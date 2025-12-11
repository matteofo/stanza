#pragma once
#include <iostream>
#include <gui/View.hpp>

namespace stanza {
    class Block: public View {
    private:
        float padding;
    public:
        float getPadding();
        void setPadding(float px);

        void render(Platform* platform, Point at) override;

        Block();
        Block(float padding);
    };
}