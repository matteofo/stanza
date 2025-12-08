#include <graphics/jobs/RenderTextJob.hpp>

namespace stanza {
    void RenderTextJob::render(Platform* platform) {
        platform->renderText(this->font, this->position, this->text);
    }

    RenderTextJob::RenderTextJob(const std::string text, Font _font, Point position) : font(_font) {
        this->text = text;
        this->position = position;
    }
}