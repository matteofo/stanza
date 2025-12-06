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
            // TODO: show an error message
            exit(1);
        }

        if (cameras.value().size() > 1) {
            // TODO: show camera selection UI
        }
        
        std::shared_ptr<libcamera::Camera> camera = cameras.value()[0];
        // sets up the camera, framebuffers and frame requests
        if (!Camera::useCamera(camera)) {
            throw new std::runtime_error(std::format("Failed to use Camera {}", camera->id()));
        }

        Font font("Roboto", 24);
        font.setColor(Color::purple());

        while (renderer->update()) {
            // this is ok cause render jobs get cleared from memory by the renderer
            RenderJob* job = new RenderTextJob("test", font, {10, 10});
            renderer->addJob(job);
            renderer->render(); // the renderer performs queued up jobs
        }

        Camera::end();
        delete renderer;
    }
}