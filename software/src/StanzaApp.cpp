#include <StanzaApp.hpp>

namespace stanza {
    StanzaApp::StanzaApp() {
        this->renderer = new SDL3Renderer();
    }

    void StanzaApp::run() {
        Font font("Roboto", 24);
        RenderJob* job = new RenderTextJob("test", font, {0, 0});

        while (renderer->update()) {
            renderer->addJob(job);
            renderer->render();
        }

        delete job;
        delete renderer;
    }
}