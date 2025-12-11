#include <StanzaApp.hpp>

namespace stanza {
    Platform* StanzaApp::globalPlatform;

    StanzaApp::StanzaApp() : logger("StanzaApp") {
        this->platform = new PlatformSDL3();
        StanzaApp::globalPlatform = this->platform;
    }

    Platform* StanzaApp::getPlatform() {
        return StanzaApp::globalPlatform;
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
        #ifdef PLATFORM_PI
        used = Camera::useCamera(camera, 3264 / 2, 2448 / 2, false);
        #else
        used = Camera::useCamera(camera, 1920, 1080, false);
        #endif

        if (!used) {
            throw new std::runtime_error(std::format("Failed to use Camera {}", camera->id()));
        }

        Font font("Roboto", 24);
        font.setColor(Color::purple());

        Font font2("Roboto", 24, FontWeight::BOLD);
        font2.setColor(Color::yellow());

        Button button;
        button.onPressed([this]() {
            this->logger.log("Button pressed!");
        });

        platform->onTouch([this](Point touch) {
            logger.log("Touch: {} {}", touch.x, touch.y);
            Storage::storeImage(Camera::getTexture());
        });

        Block* block = new Block();
        block->setSize({480, 320});

        logger.warn("{} {} {}", font.getColor().r, font.getColor().g, font.getColor().b);
        logger.warn("{} {} {}", font2.getColor().r, font2.getColor().g, font2.getColor().b);

        for (int i = 0; i < 100; i++) {
            View* text;
            if (i % 2 == 0)
                text = new Text("ho", &font2);
            else
                text = new Text("hi", &font);

            block->addChild(text);
        }

        Camera::setControl(libcamera::controls::ExposureValue, 100000);

        while (this->platform->update()) {
            // this is ok cause render jobs get cleared from memory by the platform
            RenderJob* texJob = new RenderTextureJob(Camera::getTexture(), {0, 0}, TextureFitMode::FILL);
            platform->addJob(texJob);

            block->setSize(platform->getViewport());
            block->render({0, 0});

            this->platform->render(); // the platform performs queued up jobs
        }

        Camera::end();
        delete platform;
    }
}