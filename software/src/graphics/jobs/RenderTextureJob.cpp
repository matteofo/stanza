#include <graphics/jobs/RenderTextureJob.hpp>

namespace stanza {
    void RenderTextureJob::render(Renderer* renderer) {
        renderer->renderTexture(this->texture, this->position);
    }

    RenderTextureJob::RenderTextureJob(Texture* texture, Point position) {
        this->position = position;
        this->texture = texture;
    }
}