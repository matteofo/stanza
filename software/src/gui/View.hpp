#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <util/Point.hpp>
#include <platform/Platform.hpp>

namespace stanza {
    class View {
    protected:
        std::vector<View*> children;
        View* parent;
        Point size;
        Point position;
    public:
        void addChild(View* child);
        void removeChild(View* child);
        const std::vector<View*> getChildren();

        Point getSize();
        void setSize(Point size);

        View* getParent();

        virtual void render(Platform* platform, Point at) = 0;
    };
}