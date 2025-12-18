#pragma once
#include <iostream>
#include <graphics/RenderJob.hpp>
#include <util/Rect.hpp>
#include <gui/Color.hpp>

namespace stanza {
    class RenderRectJob: public RenderJob {
    private:
        Color color;
        Rect rect;
    public:
        void render(Platform* platform) override;

        RenderRectJob(Color color, Rect rect);
    };
}