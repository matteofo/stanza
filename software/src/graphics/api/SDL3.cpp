#include <graphics/api/SDL3.hpp>

namespace stanza {
    void SDL3Renderer::init(int width, int height) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            logger.error("SDL_Init failed with {}!", SDL_GetError());
            throw new std::runtime_error("Failed to initialize SDL.");
        }

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
        SDL_free(this->renderer);
        SDL_free(this->window);

        SDL_Quit();
    }

    void SDL3Renderer::update() {
        while (SDL_PollEvent(&(this->event))) {
            if (this->event.type == SDL_EVENT_QUIT) {
                exit(0);
            }
        }
    }
}