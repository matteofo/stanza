#include <gui/Color.hpp>

namespace stanza {
    std::string to_string(Color color) {
        return std::format("{} {} {} {}", color.r, color.g, color.b, color.a);
    }
}