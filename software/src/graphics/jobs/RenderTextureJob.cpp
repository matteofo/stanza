#include <graphics/jobs/RenderTextureJob.hpp>

namespace stanza {
    void RenderTextureJob::render(Platform* platform) {
        platform->renderTexture(this->texture, this->position, this->mode);
    }

    TextureFitMode RenderTextureJob::getFitMode() {
        return this->mode;
    }

    void RenderTextureJob::setFitMode(TextureFitMode mode) {
        this->mode = mode;
    }

    Point RenderTextureJob::getPosition() {
        return this->position;
    }

    void RenderTextureJob::setPosition(Point position) {
        this->position.x = position.x;
        this->position.y = position.y;
    }

    RenderTextureJob::RenderTextureJob(Texture* texture) {
        this->texture = texture;
        this->position = {0, 0};
        this->mode = TextureFitMode::NORMAL;
    }

    RenderTextureJob::RenderTextureJob(Texture* texture, Point position) {
        this->mode = TextureFitMode::NORMAL;
        this->position = position;
        this->texture = texture;
    }

    RenderTextureJob::RenderTextureJob(Texture* texture, Point position, TextureFitMode mode) {
        this->mode = mode;
        this->position = position;
        this->texture = texture;
    }
}