#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <platform/Platform.hpp>

#ifdef PLATFORM_PI
#include <wiringPi.h>
#define BUTTON_PIN 16
#endif

namespace stanza {
    class Button {
    private:
        bool lastState;
        bool state;

        std::vector<std::function<void()>> handlers;
    public:
        bool isPressed();
        void onPressed(std::function<void()> handler);
        void update();
        Button();
    };
}