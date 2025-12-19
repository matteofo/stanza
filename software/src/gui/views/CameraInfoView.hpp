#pragma once
#include <iostream>
#include <gui/views/Block.hpp>
#include <gui/views/Text.hpp>

namespace stanza {
    class Text;
    
    class CameraInfoView: public Block {
    private:
        Text* isoText;
        Text* aptText;
        Text* spdText;
        
        static const int HEIGHT = 35;
    public:
        CameraInfoView(Platform* platform);

        void render(Point point) override;
        void update(int iso, float aperture, float shutterSpeed);
    };
}