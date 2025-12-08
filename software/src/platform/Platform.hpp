#pragma once
#include <iostream>
#include <vector>
#include <functional>

#include <graphics/Texture.hpp>
#include <graphics/RenderJob.hpp>
#include <graphics/jobs/RenderTextureJob.hpp>
#include <gui/Font.hpp>
#include <util/Point.hpp>

#ifdef __arm__
#define PLATFORM_PI
#else
#define PLATFORM_PC
#warning "Compiling for PC"
#endif

namespace stanza {
    typedef std::pair<std::string, void*> CachedFont;

    class RenderJob;
    class Font;

    class Platform {
    protected:
        // never make me get one of these
        std::vector<RenderJob*> jobs;

        std::vector<CachedFont> fontCache;
        virtual CachedFont* loadFont(Font font) = 0;

        std::vector<std::function<void(std::string code)>> keyDownHandlers;
        std::vector<std::function<void(std::string code)>> keyUpHandlers;
        std::string pressedKey;
    public:
        void addJob(RenderJob* job);
        void clearJobs();

        void onKeyDown(std::function<void(std::string)> handler);
        void onKeyUp(std::function<void(std::string)> handler);
        const std::string getPressedKey();

        virtual ~Platform() = default;

        // return false if the application should close
        virtual bool update() = 0;
        virtual void render() = 0;

        virtual void renderText(Font font, Point at, const std::string text) = 0;
    
        virtual bool renderTexture(Texture* texture);
        virtual bool renderTexture(Texture* texture, Point at, TextureFitMode mode) = 0;
        virtual Texture loadTexture(const std::string name) = 0;\
    };
}