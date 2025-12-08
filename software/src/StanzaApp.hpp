#pragma once
#include <iostream>
#include <graphics/Renderer.hpp>
#include <graphics/api/SDL3.hpp>
#include <graphics/jobs/RenderTextJob.hpp>
#include <graphics/jobs/RenderTextureJob.hpp>

#include <camera/Camera.hpp>

#include <util/Logger.hpp>

namespace stanza {
    class StanzaApp {
    private:
        Renderer* renderer;
        Logger logger;
    public:
        void run();
        StanzaApp();
    };
}