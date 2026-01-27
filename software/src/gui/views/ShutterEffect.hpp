#pragma once
#include <functional>
#include <gui/View.hpp>
#include <util/Rect.hpp>
#include <platform/Platform.hpp>
#include <graphics/jobs/RenderRectJob.hpp>

#define SHUTTER_EFFECT_SHUTTER_LENGTH 20
#define SHUTTER_EFFECT_FADE_LENGTH 100

namespace stanza {
    class ShutterEffect: public View {
    private:
        int frame = 0;
        std::function<void()> doneCallback;
    public:
        Point getSize();
        void render(Point at) override;

        void onDone(std::function<void()> callback);

        using View::View;
    };
}