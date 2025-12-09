#include <util/Point.hpp>

namespace stanza {
    bool Point::operator!=(const Point& right) {
        return !this->operator==(right);
    }

    bool Point::operator==(const Point& right) {
        return this->x == right.x && this->y == right.y;
    }
}