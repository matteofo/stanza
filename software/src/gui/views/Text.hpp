#pragma once
#include <iostream>
#include <gui/View.hpp>
#include <gui/Font.hpp>
#include <graphics/jobs/RenderTextJob.hpp>

namespace stanza {
    class Text: public View {
    private:
        std::string text;
        Font* font;
    public:
        void setText(const std::string text);
        const std::string getText();

        Point getSize() override;

        void render(Point at) override;

        Text(Platform* platform, const std::string text, Font* font);
    };
}