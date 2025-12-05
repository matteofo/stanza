#include <graphics/api/SDL3.hpp>

namespace stanza {
    void SDL3Renderer::init(int width, int height) {
        #ifdef __arm__ // assume we're compiling on rpi
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

        this->window = SDL_CreateWindow("SDL3 Renderer", width, height, 0);
        this->renderer = SDL_CreateRenderer(this->window, NULL);
    }

    SDL3Renderer::SDL3Renderer(int width, int height) : logger("SDL3Renderer") {
        this->init(width, height);
    }

    SDL3Renderer::SDL3Renderer() : logger("SDL3Renderer") {
        this->init(480, 320);
    }

    SDL3Renderer::~SDL3Renderer() {
        logger.log("Cleaning up SDL3...");
        
        TTF_Quit();
        SDL_Quit();
    }

    bool SDL3Renderer::update() {
        while (SDL_PollEvent(&(this->event))) {
            if (this->event.type == SDL_EVENT_QUIT) {
                return false;
            }
        }

        return true;
    }

    void SDL3Renderer::render() {
        // clear white by default
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        // enable alpha blending
        SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderClear(this->renderer);

        // render stuff in queue
        for (auto& job : this->jobs) {
            job->render(this);
        }

        SDL_RenderPresent(this->renderer);
    
        this->clearJobs();
    }

    Texture SDL3Renderer::loadTexture(const std::string name) {
        logger.log("Loading texture \"{}\"", name);
        Texture t(1, 1);
        return t;
    }

    void SDL3Renderer::renderText(Font font, Point at, const std::string text) {
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

        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surf);
        SDL_FRect rect = {at.x, at.y, (float) surf->w, (float) surf->h};

        SDL_RenderTexture(this->renderer, texture, NULL, &rect);

        SDL_DestroySurface(surf);
        SDL_DestroyTexture(texture);
    }

    CachedFont* SDL3Renderer::loadFont(Font font) {
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