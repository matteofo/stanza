#include <platform/Button.hpp>

namespace stanza {
    bool Button::isPressed() {
        return this->state;
    }

    void Button::onPressed(std::function<void()> handler) {
        this->handlers.push_back(handler);
    }

    void Button::update() {
        this->lastState = this->state;
        #ifdef PLATFORM_PI
        this->state = digitalRead(BUTTON_PIN);
        #else
        this->state = false;
        #endif

        if (this->lastState != this->state && this->state) {
            for (auto& handler : this->handlers) {
                if (handler) handler();
            }
        }
    }

    Button::Button() {
        #ifdef PLATFORM_PI
        wiringPiSetupGpio();
        pinMode(BUTTON_PIN, INPUT);
        pullUpDnControl(BUTTON_PIN, PUD_DOWN);
        #endif
    }
}