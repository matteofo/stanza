#include <gui/views/Text.hpp>

namespace stanza {
    void Text::setText(const std::string text) {
        this->text = text;
    }

    const std::string Text::getText() {
        return this->text;
    }

    Text::Text(const std::string text, Font font) {     
        this->text = text;
        this->font = &font;
        this->size = {0, 0};
    }

    void Text::render(Platform* platform, Point at) {
        this->size = platform->getTextSize(*(this->font), this->text);
        RenderJob* job = new RenderTextJob(this->text, *(this->font), at);
        platform->addJob(job);
    }
}