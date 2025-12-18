#include <StanzaApp.hpp>

namespace stanza {
    StanzaApp::StanzaApp() : logger("StanzaApp") {
        this->platform = new PlatformSDL3();
    }

    void StanzaApp::run() {
        View* cameraView = new CameraView(this->platform);

        while (this->platform->update()) {
            cameraView->render();

            this->platform->render(); // queued up jobs are rendered
        }

        delete this->platform;
    }
}