#pragma once
#include <iostream>
#include <graphics/Renderer.hpp>
#include <graphics/api/SDL3.hpp>
#include <graphics/jobs/RenderTextJob.hpp>

namespace stanza {
    class StanzaApp {
    private:
        Renderer* renderer;
    public:
        void run();
        StanzaApp();
    };
}