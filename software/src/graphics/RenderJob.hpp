#pragma once
#include <iostream>
#include <graphics/Renderer.hpp>

namespace stanza {
    class Renderer;

    class RenderJob {
    public:
        virtual void render(Renderer* renderer) = 0;
    };
}