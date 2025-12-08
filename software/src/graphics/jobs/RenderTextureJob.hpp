#pragma once
#include <iostream>
#include <graphics/Renderer.hpp>
#include <graphics/RenderJob.hpp>
#include <graphics/Texture.hpp>
#include <util/Point.hpp>

namespace stanza {
    class RenderTextureJob: public RenderJob {
    private:
        Texture* texture;
        Point position;
        TextureFitMode mode;
    public:
        TextureFitMode getFitMode();
        void setFitMode(TextureFitMode mode);

        Point getPosition();
        void setPosition(Point point);

        void render(Renderer* renderer) override;

        RenderTextureJob(Texture* texture);
        RenderTextureJob(Texture* texture, Point position);
        RenderTextureJob(Texture* texture, Point position, TextureFitMode mode);
    };
}