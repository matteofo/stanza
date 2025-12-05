#include <graphics/Renderer.hpp>

namespace stanza {
    void Renderer::addJob(RenderJob* job) {
        this->jobs.push_back(job);
    }

    void Renderer::clearJobs() {
        this->jobs.clear();
    }
}