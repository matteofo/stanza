#pragma once
#include <iostream>
#include <graphics/Texture.hpp>
#include <graphics/Renderer.hpp>
#include <util/Logger.hpp>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace stanza {
    class SDL3Renderer: public Renderer {
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Event event;

        Logger logger;

        void init(int width, int height);
        virtual CachedFont* loadFont(Font font) override;
    public:
        bool update() override;
        void render() override;

        void renderText(Font font, Point at, const std::string text) override;

        Texture loadTexture(const std::string name) override;
        bool renderTexture(Texture* texture, Point at, TextureFitMode mode) override;

        SDL3Renderer(int width, int height);
        SDL3Renderer();
        ~SDL3Renderer();
    };
};