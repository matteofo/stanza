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
#include <gui/views/CameraInfoView.hpp>
#include <gui/views/ShutterEffect.hpp>

namespace stanza {
    class Block;

    class CameraView: public View {
    private:
        Logger logger;
        Block* block;
        CameraInfoView* info;
    public:
        CameraView(Platform* platform);
        ~CameraView();

        void render(Point at) override;
    };
}