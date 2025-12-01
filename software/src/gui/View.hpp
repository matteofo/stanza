#pragma once
#include <iostream>
#include <vector>
#include <memory>

namespace stanza {
    class View {
    protected:
        std::vector<View*> children;
        View* parent;
    public:
        void addChild(View* child);
        void removeChild(View* child);
        const std::vector<View*> getChildren();

        View* getParent();

        virtual void render() = 0;
    };
}