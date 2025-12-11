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
        View* cameraView = new CameraView();

        while (this->platform->update()) {
            cameraView->render();

            this->platform->render(); // queued up jobs are rendered
        }

        delete StanzaApp::globalPlatform;
    }
}