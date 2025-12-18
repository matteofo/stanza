#pragma once
#include <iostream>
#include <graphics/jobs/RenderRectJob.hpp>
#include <gui/View.hpp>
#include <gui/Color.hpp>

namespace stanza {
    class Block: public View {
    private:
        float padding;
        Color backgroundColor;
    public:
        float getPadding();
        void setPadding(float px);

        Color getBackgroundColor();
        void setBackgroundColor(Color color);

        void render(Point at) override;

        Block(Platform* platform);
        Block(Platform* platform, Color bgColor);
        Block(Platform* platform, float padding);
        Block(Platform* platform, float padding, Color bgColor);
    };
}