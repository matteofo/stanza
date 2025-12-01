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

    View* View::getParent() {
        return this->parent;
    }
}
