#pragma once
#include <iostream>
#include <vector>

namespace stanza {
    enum PixelFormat {
        RGBA_32
    };

    // returns the size (in bytes) of a pixel in the specified format
    int pixel_format_size(PixelFormat format);

    class Texture {
    protected:
        void* raw;
        int width, height;
        PixelFormat format;
    public:
        void* getRaw();

        int getWidth();
        int getHeight();
        PixelFormat getFormat();

        Texture(int width, int height, PixelFormat format);
        Texture(int width, int height);
        ~Texture();
    };
}