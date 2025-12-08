#pragma once
#include <iostream>
#include <print>
#include <platform/Platform.hpp>
#include <graphics/RenderJob.hpp>
#include <gui/Font.hpp>
#include <util/Point.hpp>

namespace stanza {
    class RenderTextJob: public RenderJob {
    private:
        std::string text;
        Font font;
        Point position;
    public:
        void render(Platform* platform) override;
        RenderTextJob(const std::string text, Font _font, Point position);
    };
}