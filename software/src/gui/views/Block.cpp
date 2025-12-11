#include <gui/views/Block.hpp>

namespace stanza {
    float Block::getPadding() {
        return this->padding;
    }

    void Block::setPadding(float px) {
        this->padding = px;
    }

    void Block::render(Point at) {
        Point pos = {this->padding, this->padding};
        float step = 0;

        for (auto& child : this->children) {
            Point cs = child->getSize();

            if (cs.x + padding >= this->size.x - pos.x) {
                pos.x = this->padding;
                pos.y += cs.y + this->padding;
            }

            child->render({
                this->position.x + pos.x,
                this->position.y + pos.y,
            });

            pos.x += cs.x + this->padding;
        }
    }

    Block::Block() {
        this->padding = 10;
    }

    Block::Block(float padding) {
        this->padding = padding;
    }
}