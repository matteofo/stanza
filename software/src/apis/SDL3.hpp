#pragma once
#include <iostream>
#include <graphics/Texture.hpp>
#include <platform/Platform.hpp>
#include <util/Logger.hpp>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace stanza {
    class PlatformSDL3: public Platform {
    private:
        SDL_Renderer* platform;
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

        PlatformSDL3(int width, int height);
        PlatformSDL3();
        ~PlatformSDL3();
    };
};