#include <gui/Font.hpp>

namespace stanza {
    const std::string to_string(FontWeight weight) {
        switch (weight) {
            case LIGHT:
                return "Light";
            case REGULAR:
                return "Regular";
            case MEDIUM:
                return "Medium";
            case HEAVY:
                return "Heavy";
            case SEMIBOLD:
                return "Semibold";
            case BOLD:
                return "Bold";
        }
    }

    unsigned int Font::getSize() {
        return this->size;
    }

    const std::string Font::getName() {
        return this->name;
    }

    FontWeight Font::getWeight() {
        return this->weight;
    }

    Color Font::getColor() {
        return this->color;
    }

    void Font::setColor(Color color) {
        this->color.r = color.r;
        this->color.g = color.g;
        this->color.b = color.b;
    }

    Font::Font(Font& _font) {
        this->name = _font.name;
        this->weight = _font.weight;
        this->size = _font.size;
        this->color = _font.color;
    }

    Font::Font(const std::string name) {
        this->name = name;
        this->weight = REGULAR;
        this->size = 24;
        this->color = Color::black();
    }

    Font::Font(const std::string name, unsigned int size) {
        this->name = name;
        this->weight = REGULAR;
        this->size = size;
        this->color = Color::black();
    }

    Font::Font(const std::string name, unsigned int size, FontWeight weight) {
        this->name = name;
        this->weight = weight;
        this->size = size;
        this->color = Color::black();
    }
}