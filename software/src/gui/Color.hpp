#pragma once
#include <util/types.hpp>

namespace stanza {
    struct Color {
        u8 r;
        u8 g;
        u8 b;
        u8 a;        

        const static Color black() {
            return {0, 0, 0, 255};
        }

        const static Color white() {
            return {255, 255, 255, 255};
        }

        const static Color red() {
            return {255, 0, 0, 255};
        }

        const static Color orange() {
            return {255, 165, 0, 255};
        }

        const static Color yellow() {
            return {255, 255, 0, 255};
        }

        const static Color green() {
            return {0, 255, 0, 255};
        }

        const static Color blue() {
            return {0, 0, 255, 255};
        }

        const static Color purple() {
            return {165, 0, 255, 255};
        }

        const static Color pink() {
            return {255, 0, 255, 255};
        }
    };
}