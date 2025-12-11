#include <gui/views/Text.hpp>

namespace stanza {
    void Text::setText(const std::string text) {
        this->text = text;
    }

    const std::string Text::getText() {
        return this->text;
    }

    Text::Text(const std::string text, Font* font) {     
        this->text = text;
        this->font = font;
        this->size = {0, 0};
    }

    Point Text::getSize() {
        return StanzaApp::getPlatform()->getTextSize(*(this->font), this->text);
    }

    void Text::render(Point at) {
        this->size = StanzaApp::getPlatform()->getTextSize(*(this->font), this->text);
        RenderJob* job = new RenderTextJob(this->text, *(this->font), at);
        StanzaApp::getPlatform()->addJob(job);
    }
}