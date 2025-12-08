#include <graphics/Renderer.hpp>

namespace stanza {
    void Renderer::addJob(RenderJob* job) {
        this->jobs.push_back(job);
    }

    void Renderer::clearJobs() {
        for (auto& job : this->jobs) {
            delete job;
        }
        this->jobs.clear();
    }

    bool Renderer::renderTexture(Texture* texture) {
        return this->renderTexture(texture, {0, 0}, TextureFitMode::NORMAL);
    }
}