#pragma once 
#include <iostream>

namespace stanza {
    struct Point {
        float x, y;
        bool operator!=(const Point& right);
        bool operator==(const Point& right);
    };
}