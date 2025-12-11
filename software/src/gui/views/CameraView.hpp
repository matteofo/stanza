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
#include <gui/views/Block.hpp>
#include <gui/views/Text.hpp>

namespace stanza {
    class CameraView: public View {
    private:
        Logger logger;
        Block* block;
    public:
        CameraView();
        ~CameraView();

        void render(Point at) override;
    };
}