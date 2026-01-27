#include <gui/views/ShutterEffect.hpp>

namespace stanza {
    void ShutterEffect::render(Point at) {
        Point viewport = this->platform->getViewport();

        if (++frame > SHUTTER_EFFECT_SHUTTER_LENGTH) {
            int fadeFrame = frame - SHUTTER_EFFECT_SHUTTER_LENGTH;
            if (fadeFrame > SHUTTER_EFFECT_FADE_LENGTH) {
                this->doneCallback();
                return;
            } 

            Rect rect = {0, 0, viewport.x, viewport.y};
            Color color = Color::white();
            color.a = 255 - (u8)(((double)fadeFrame / SHUTTER_EFFECT_FADE_LENGTH) * 255);

            RenderRectJob* fadeJob = new RenderRectJob(color, rect);
            this->platform->addJob(fadeJob);

            return;
        }
        
        Rect top;
        top.x = 0;
        top.y = 0;
        top.w = viewport.x;
        top.h = (viewport.y / 2 * (double)frame / SHUTTER_EFFECT_SHUTTER_LENGTH);

        Rect bottom;
        bottom.x = 0;
        bottom.y = (viewport.y - (viewport.y / 2 * (double)frame / SHUTTER_EFFECT_SHUTTER_LENGTH));
        bottom.w = viewport.x;
        bottom.h = (viewport.y / 2);

        RenderRectJob* topJob = new RenderRectJob(Color::white(), top);
        RenderRectJob* bottomJob = new RenderRectJob(Color::white(), bottom);

        this->platform->addJob(topJob);
        this->platform->addJob(bottomJob);
    }

    Point ShutterEffect::getSize() {
        return this->platform->getViewport();
    }
    
    void ShutterEffect::onDone(std::function<void()> callback) {
        this->doneCallback = callback;
    }
}