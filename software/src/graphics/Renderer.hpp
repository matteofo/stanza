#pragma once
#include <iostream>
#include <graphics/Texture.hpp>

namespace stanza {
    class Renderer {
    public:
        virtual Texture loadTexture(const std::string name);

        virtual void update();
        virtual void render();
    };
}