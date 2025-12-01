#pragma once
#include <iostream>
#include <graphics/Texture.hpp>
#include <graphics/Renderer.hpp>
#include <util/Logger.hpp>

#include <SDL3/SDL.h>

namespace stanza {
    class SDL3Renderer: public Renderer {
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Event event;

        Logger logger;

        void init(int width, int height);
    public:
        void update() override;
        void render() override;
        Texture loadTexture(const std::string name) override;

        SDL3Renderer(int width, int height);
        SDL3Renderer();
        ~SDL3Renderer();
    };
};