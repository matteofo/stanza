#include <apis/SDL3.hpp>

namespace stanza {
    void PlatformSDL3::init(int width, int height) {
        #ifdef PLATFORM_PI // assume we're compiling on rpi
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "kmsdrm");
        SDL_SetHint(SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER, "0");
        #endif

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            logger.error("SDL_Init failed with {}!", SDL_GetError());
            throw new std::runtime_error("Failed to initialize SDL.");
        }

        if (!TTF_Init()) {
            logger.error("TTF_Init failed with {}!", SDL_GetError());
            throw new std::runtime_error("Failed to initialize SDL_ttf.");
        }

        logger.log("Initialized SDL3 backend.");

        this->window = SDL_CreateWindow("SDL3 Platform", width, height, SDL_WINDOW_RESIZABLE);
        this->platform = SDL_CreateRenderer(this->window, NULL);
    }

    PlatformSDL3::PlatformSDL3(int width, int height) : logger("PlatformSDL3") {
        this->init(width, height);
    }

    PlatformSDL3::PlatformSDL3() : logger("PlatformSDL3") {
        this->init(480, 320);
    }

    PlatformSDL3::~PlatformSDL3() {
        logger.log("Cleaning up SDL3...");
        
        TTF_Quit();
        SDL_Quit();
    }

    bool PlatformSDL3::update() {
        while (SDL_PollEvent(&(this->event))) {
            switch(this->event.type) {
                case SDL_EVENT_QUIT:
                    return false;
                case SDL_EVENT_KEY_DOWN:
                    this->pressedKey = SDL_GetKeyName(this->event.key.key);

                    if (!this->event.key.repeat) {
                        for (auto& handler : this->keyDownHandlers) {
                            if (handler) {
                                handler(this->pressedKey);
                            }
                        }
                    }
                    break;
                case SDL_EVENT_KEY_UP:
                    this->pressedKey = "";

                    if (!this->event.key.repeat) {
                        std::string key = SDL_GetKeyName(this->event.key.key);

                        for (auto& handler : this->keyUpHandlers) {
                            if (handler) {
                                handler(key);
                            }
                        }
                    }
                    break;
            }
        }

        return true;
    }

    void PlatformSDL3::render() {
        // clear black by default
        SDL_SetRenderDrawColor(this->platform, 0, 0, 0, 255);
        // enable alpha blending
        SDL_SetRenderDrawBlendMode(this->platform, SDL_BLENDMODE_BLEND);
        SDL_RenderClear(this->platform);

        // render stuff in queue
        for (auto& job : this->jobs) {
            job->render(this);
        }

        SDL_RenderPresent(this->platform);
        this->clearJobs();
    }

    Texture PlatformSDL3::loadTexture(const std::string name) {
        logger.log("Loading texture \"{}\"", name);
        Texture t(1, 1);
        return t;
    }

    bool PlatformSDL3::renderTexture(Texture* texture, Point at, TextureFitMode mode) {
        if (texture == NULL || texture->getRaw() == NULL) {
            logger.error("Null texture!");
            return false;
        }

        SDL_Surface* surface = SDL_CreateSurfaceFrom(
            texture->getWidth(),
            texture->getHeight(),
            SDL_PIXELFORMAT_YUY2,
            texture->getRaw(),
            texture->getPitch()
        );

        if (surface == NULL) {
            logger.error("Null surface!");
            return false;
        }

        SDL_Texture* tex = SDL_CreateTextureFromSurface(this->platform, surface);
        if (tex == NULL) {
            logger.error("Null SDL texture!");
            return false;
        }

        SDL_FRect dst = {at.x, at.y, surface->w, surface->h};
        
        switch (mode) {
            case NORMAL:
                SDL_RenderTexture(this->platform, tex, NULL, &dst);
                break;
            case FILL:
                SDL_RenderTexture(this->platform, tex, NULL, NULL);
                break;
            case FIT:
                throw std::logic_error("TextureFillMode::FIT is not implemented!");
                break;
        }

        SDL_DestroySurface(surface);
        SDL_DestroyTexture(tex);

        return true;
    }

    void PlatformSDL3::renderText(Font font, Point at, const std::string text) {
        CachedFont* loaded = this->loadFont(font);
        if (!loaded) {
            return;
        }

        TTF_Font* sdlFont = (TTF_Font*) loaded->second;
        SDL_Surface* surf = TTF_RenderText_Blended(sdlFont, text.c_str(), 0, {
            .r = font.getColor().r,
            .g = font.getColor().g,
            .b = font.getColor().b
        });

        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->platform, surf);
        SDL_FRect rect = {at.x, at.y, (float) surf->w, (float) surf->h};

        SDL_RenderTexture(this->platform, texture, NULL, &rect);

        SDL_DestroySurface(surf);
        SDL_DestroyTexture(texture);
    }

    CachedFont* PlatformSDL3::loadFont(Font font) {
        for (auto& f : this->fontCache) {
            if (f.first == font.getName()) {
                return &f;
            }
        }

        logger.log("Loading font {}", font.getName());

        std::string fontPath = std::format("./res/fonts/{}-{}.ttf", font.getName(), stanza::to_string(font.getWeight()));
        TTF_Font* sdlFont = TTF_OpenFont(fontPath.c_str(), font.getSize());
        
        if (!sdlFont) {
            logger.error("Failed to load font {}!", font.getName());
            return nullptr;
        }

        CachedFont entry;
        entry.first = font.getName();
        entry.second = sdlFont;

        this->fontCache.push_back(entry);
        return &this->fontCache[this->fontCache.size() - 1];
    }
}