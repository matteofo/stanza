#include <graphics/jobs/RenderRectJob.hpp>

namespace stanza {
    void RenderRectJob::render(Platform* platform) {
        platform->renderRect(this->color, this->rect);
    }

    RenderRectJob::RenderRectJob(Color color, Rect rect) {
        this->color = color;
        this->rect = rect;
    }
}