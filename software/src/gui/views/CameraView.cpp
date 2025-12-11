#include <gui/views/CameraView.hpp>

namespace stanza {
    CameraView::CameraView() : logger("CameraView") {
        if (!Camera::init()) {
            logger.error("Failed to init() Camera!"); 
            throw new std::runtime_error("Failed to init() Camera!");
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
            logger.error("Failed to use Camera {}", camera->id());
            throw new std::runtime_error(std::format("Failed to use Camera {}", camera->id()));
        }

        Font* font = new Font("Roboto", 24);
        font->setColor(Color::purple());

        Font* font2 = new Font("Roboto", 24, FontWeight::BOLD);
        font2->setColor(Color::yellow());

        StanzaApp::getPlatform()->onTouch([this](Point touch) {
            logger.log("Touch: {} {}", touch.x, touch.y);
            Storage::storeImage(Camera::getTexture());
        });

        this->block = new Block();
        this->block->setSize(StanzaApp::getPlatform()->getViewport());

        // for (int i = 0; i < 100; i++) {
        //     View* text;
        //     if (i % 2 == 0)
        //         text = new Text("ho", font2);
        //     else
        //         text = new Text("hi", font);
        // 
        //     this->block->addChild(text);
        // }

        this->addChild(this->block);
    }

    CameraView::~CameraView() {
        Camera::end();
    }

    void CameraView::render(Point at) {
        RenderJob* texJob = new RenderTextureJob(Camera::getTexture(), {0, 0}, TextureFitMode::FILL);
        StanzaApp::getPlatform()->addJob(texJob);

        this->block->setSize(StanzaApp::getPlatform()->getViewport());

        for (auto& child : this->children) {
            child->render(at);
        }
    }
}