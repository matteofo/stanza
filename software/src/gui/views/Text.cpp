#include <gui/views/Text.hpp>

namespace stanza {
    void Text::setText(const std::string text) {
        this->text = text;
    }

    const std::string Text::getText() {
        return this->text;
    }

    Text::Text(Platform* platform, const std::string text, Font* font) : View(platform) {     
        this->text = text;
        this->font = font;
        this->size = {0, 0};
    }

    Point Text::getSize() {
        return this->platform->getTextSize(*(this->font), this->text);
    }

    void Text::render(Point at) {
        this->size = platform->getTextSize(*(this->font), this->text);
        RenderJob* job = new RenderTextJob(this->text, *(this->font), at);
        platform->addJob(job);
    }
}