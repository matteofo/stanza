#pragma once
#include <iostream>
#include <graphics/RenderJob.hpp>
#include <platform/Platform.hpp>
#include <graphics/Texture.hpp>
#include <util/Point.hpp>

namespace stanza {
    class Platform;

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

        void render(Platform* platform) override;

        RenderTextureJob(Texture* texture);
        RenderTextureJob(Texture* texture, Point position);
        RenderTextureJob(Texture* texture, Point position, TextureFitMode mode);
    };
}