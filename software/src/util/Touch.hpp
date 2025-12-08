#pragma once

#include <iostream>
#include <optional>

#include <util/Point.hpp>

namespace stanza {
    enum GestureType {
        SWIPE_UP,
        SWIPE_DOWN,
        SWIPE_LEFT,
        SWIPE_RIGHT
    };

    class TouchProvider {
    protected:
        Point lastTouch;
    public:
        virtual std::optional<Point> getTouch() = 0;
    };
}