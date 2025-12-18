#include <gui/views/Block.hpp>

namespace stanza {
    float Block::getPadding() {
        return this->padding;
    }

    void Block::setPadding(float px) {
        this->padding = px;
    }

    Color Block::getBackgroundColor() {
        return this->backgroundColor;
    }

    void Block::setBackgroundColor(Color color) {
        this->backgroundColor = color;
    }

    void Block::render(Point at) {
        RenderJob* job = new RenderRectJob(this->backgroundColor, {this->position.x, this->position.y, this->size.x, this->size.y});
        this->platform->addJob(job);

        Point pos = {this->padding, this->padding};

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

    Block::Block(Platform* platform) : View(platform) {
        this->padding = 10;
    }

    Block::Block(Platform* platform, Color bgColor) : View(platform) {
        this->padding = 10;
        this->backgroundColor = bgColor;
    }

    Block::Block(Platform* platform, float padding) : View(platform) {
        this->padding = padding;
    }

    Block::Block(Platform* platform, float padding, Color bgColor) : View(platform) {
        this->padding = padding;
        this->backgroundColor = bgColor;
    }
}