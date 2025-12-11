#include <gui/views/Block.hpp>

namespace stanza {
    float Block::getPadding() {
        return this->padding;
    }

    void Block::setPadding(float px) {
        this->padding = px;
    }

    void Block::render(Platform* platform, Point at) {
        Point pos = {this->padding, this->padding};
        float step = 0;

        for (auto& child : this->children) {
            Point nextPos;

            child->render(platform, {
                this->position.x + pos.x,
                this->position.y + pos.y,
            });
            
            nextPos = {
                pos.x + child->getSize().x + padding,
                pos.y
            };

            if (nextPos.x >= this->size.x + padding) {
                nextPos.y += child->getSize().y + padding;
                nextPos.x = padding;
            }

            pos.x = nextPos.x;
            pos.y = nextPos.y;
        }
    }

    Block::Block() {
        this->padding = 10;
    }

    Block::Block(float padding) {
        this->padding = padding;
    }
}