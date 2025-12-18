#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <util/Point.hpp>
#include <platform/Platform.hpp>

namespace stanza {
    class View {
    protected:
        Platform* platform;

        std::vector<View*> children;
        View* parent;
        
        Point size;
        Point position;
    public:
        virtual void addChild(View* child);
        virtual void removeChild(View* child);
        const std::vector<View*> getChildren();

        virtual Point getSize();
        virtual void setSize(Point size);

        virtual View* getParent();

        virtual void render(Point at) = 0;
        virtual void render();

        View(Platform* platform);
        virtual ~View();
    };
}

#include <StanzaApp.hpp>