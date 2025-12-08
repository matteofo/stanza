#include <platform/Platform.hpp>

namespace stanza {
    void Platform::addJob(RenderJob* job) {
        this->jobs.push_back(job);
    }

    void Platform::clearJobs() {
        for (auto& job : this->jobs) {
            delete job;
        }
        this->jobs.clear();
    }

    bool Platform::renderTexture(Texture* texture) {
        return this->renderTexture(texture, {0, 0}, TextureFitMode::NORMAL);
    }

    void Platform::onKeyDown(std::function<void(std::string)> handler) {
        this->keyDownHandlers.push_back(handler);
    }

    void Platform::onKeyUp(std::function<void(std::string)> handler) {
        this->keyUpHandlers.push_back(handler);
    }

    const std::string Platform::getPressedKey() {
        return this->pressedKey;
    }
}