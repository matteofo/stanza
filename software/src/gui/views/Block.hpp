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

        void render(Point at) override;

        Block();
        Block(float padding);
    };
}