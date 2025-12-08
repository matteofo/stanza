#pragma once
#include <iostream>

namespace stanza {
    class Platform;

    class RenderJob {
    public:
        virtual void render(Platform* platform) = 0;
    };
}

#include <platform/Platform.hpp>