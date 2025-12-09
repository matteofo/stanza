#pragma once
#include <iostream>

#include <platform/Platform.hpp>
#include <platform/Button.hpp>
#include <platform/Storage.hpp>
#include <apis/SDL3.hpp>
#include <graphics/jobs/RenderTextJob.hpp>
#include <graphics/jobs/RenderTextureJob.hpp>
#include <camera/Camera.hpp>
#include <util/Logger.hpp>

namespace stanza {
    class StanzaApp {
    private:
        Platform* platform;
        Logger logger;
    public:
        void run();
        StanzaApp();
    };
}