#include <StanzaApp.hpp>

namespace stanza {
    StanzaApp::StanzaApp() : logger("StanzaApp") {
        this->renderer = new SDL3Renderer();
    }

    void StanzaApp::run() {
        if (!Camera::init()) {
            throw new std::runtime_error("Failed to init() Camera");
        }

        auto cameras = Camera::enumerate();
        if (!cameras.has_value()) {
            exit(1);
        }

        if (cameras.value().size() > 1) {
            // TODO: show camera selection UI
        } else {
            Camera::useCamera(cameras.value()[0]);
        }

        if (!Camera::allocateBuffers()) {
            exit(1);
        }

        Font font("Roboto", 24);
        font.setColor(Color::purple());

        while (renderer->update()) {
            // this is ok cause render jobs get cleared from memory by the renderer
            RenderJob* job = new RenderTextJob("test", font, {10, 10});
            renderer->addJob(job);
            renderer->render();
        }

        Camera::end();
        delete renderer;
    }
}