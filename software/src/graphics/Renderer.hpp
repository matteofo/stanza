#pragma once
#include <iostream>
#include <vector>

#include <graphics/Texture.hpp>
#include <graphics/RenderJob.hpp>
#include <graphics/jobs/RenderTextureJob.hpp>
#include <gui/Font.hpp>
#include <util/Point.hpp>

namespace stanza {
    typedef std::pair<std::string, void*> CachedFont;

    class RenderJob;
    class Font;

    class Renderer {
    protected:
        // never make me get one of these
        std::vector<RenderJob*> jobs;

        std::vector<CachedFont> fontCache;
        virtual CachedFont* loadFont(Font font) = 0;
    public:
        void addJob(RenderJob* job);
        void clearJobs();

        virtual ~Renderer() = default;

        // return false if the application should close
        virtual bool update() = 0;
        virtual void render() = 0;

        virtual void renderText(Font font, Point at, const std::string text) = 0;
    
        virtual bool renderTexture(Texture* texture);
        virtual bool renderTexture(Texture* texture, Point at, TextureFitMode mode) = 0;
        virtual Texture loadTexture(const std::string name) = 0;
    };
}