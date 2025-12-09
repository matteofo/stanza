#include <StanzaApp.hpp>

namespace stanza {
    StanzaApp::StanzaApp() : logger("StanzaApp") {
        this->platform = new PlatformSDL3();
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
        bool used = false;
        #ifdef PLATORM_PI
        used = Camera::useCamera(camera, 3264 / 2, 2448 / 2, true)
        #else
        used = Camera::useCamera(camera, 1920, 1080, false);
        #endif

        if (!used) {
            throw new std::runtime_error(std::format("Failed to use Camera {}", camera->id()));
        }

        Font font("Roboto", 24);
        font.setColor(Color::purple());

        Button button;
        button.onPressed([this]() {
            this->logger.log("Button pressed!");
        });

        platform->onTouch([this](Point touch) {
            logger.log("Touch: {} {}", touch.x, touch.y);
            Storage::storeImage(Camera::getTexture());
        });
        
        while (this->platform->update()) {
            // this is ok cause render jobs get cleared from memory by the platform
            RenderJob* texJob = new RenderTextureJob(Camera::getTexture(), {0, 0}, TextureFitMode::FILL);
            platform->addJob(texJob);

            RenderJob* job = new RenderTextJob("test", font, {10, 10});
            this->platform->addJob(job);
            
            this->platform->render(); // the platform performs queued up jobs
        }

        Camera::end();
        delete platform;
    }
}