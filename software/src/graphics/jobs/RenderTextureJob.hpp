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
    public:
        void render(Renderer* renderer) override;
        RenderTextureJob(Texture* texture, Point position);
    };
}