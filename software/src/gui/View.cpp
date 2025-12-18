#include "View.hpp"

namespace stanza {
    void View::addChild(View* child) {
        this->children.push_back(child);
        child->parent = this;
    }

    void View::removeChild(View* child) {
        auto it = std::find(this->children.begin(), this->children.end(), child);
        if (it != this->children.end()) {
            child->parent = nullptr;
            this->children.erase(it);
        }
    }

    const std::vector<View*> View::getChildren() {
        return this->children;
    }

    void View::setSize(Point size) {
        this->size.x = size.x;
        this->size.y = size.y;
    }

    Point View::getSize() {
        return this->size;
    }

    View* View::getParent() {
        return this->parent;
    }

    View::View(Platform* platform) {
        this->platform = platform;
    }

    View::~View() {
        for (auto& child : this->children) {
            delete child;
        }
    }

    void View::render() {
        this->render({0, 0});
    }
}
