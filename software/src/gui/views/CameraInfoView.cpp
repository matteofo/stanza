#include <gui/views/CameraInfoView.hpp>

namespace stanza {
    CameraInfoView::CameraInfoView(Platform* platform) : Block(platform, {45, 45, 45, 127}) {
        Font* font = new Font("Roboto", 14);
        font->setColor({255, 255, 255, 255});

        this->isoText = new Text(platform, "ISO 0", font);
        this->aptText = new Text(platform, "APT 0", font);
        this->spdText = new Text(platform, "SPD 0/0", font);

        this->addChild(this->isoText);
        this->addChild(this->aptText);
        this->addChild(this->spdText);

        Point viewport = platform->getViewport();
        this->setSize({viewport.x, CameraInfoView::HEIGHT});
        this->position = {0, viewport.y - CameraInfoView::HEIGHT};
    }

    void CameraInfoView::render(Point at) {
        Point viewport = platform->getViewport();
        this->setSize({viewport.x, CameraInfoView::HEIGHT});
        this->position = {0, viewport.y - CameraInfoView::HEIGHT};

        Block::render(at);
    }

    void CameraInfoView::update(int iso, float aperture, float shutterSpeed) {
        this->isoText->setText(std::format("ISO {}", iso));
        this->aptText->setText(std::format("APT {}", aperture));
        this->spdText->setText(std::format("SPD {}", shutterSpeed));
    }
}