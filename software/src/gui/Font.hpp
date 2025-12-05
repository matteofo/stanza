#pragma once
#include <iostream>
#include <graphics/Renderer.hpp>
#include <gui/Color.hpp>

namespace stanza {
    enum FontWeight {
        LIGHT = -1,
        REGULAR = 0,
        MEDIUM,
        HEAVY,
        SEMIBOLD,
        BOLD
    };

    const std::string to_string(FontWeight weight);

    class Font {
    private:
        unsigned int size;
        std::string name;
        FontWeight weight;
        Color color;
    public:
        unsigned int getSize();
        const std::string getName();
        FontWeight getWeight();
        Color getColor();

        Font& setColor(Color color);

        Font(Font& _font);
        Font(const std::string name);
        Font(const std::string name, unsigned int size);
        Font(const std::string name, unsigned int size, FontWeight weight);
    };
}