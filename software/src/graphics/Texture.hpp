#pragma once
#include <iostream>
#include <vector>

#include <util/types.hpp>

namespace stanza {
    enum PixelFormat {
        OTHER,
        RGBA_32
    };

    // returns the size (in bytes) of a pixel in the specified format
    u8 pixel_format_size(PixelFormat format);

    class Texture {
    protected:
        void* raw;
        u64 width, height, stride;
        PixelFormat format;
    public:
        void* getRaw();
        void blit(void* source, u64 size);

        u64 getWidth();
        u64 getHeight();
        u64 getStride();
        PixelFormat getFormat();

        Texture(u64 width, u64 height, PixelFormat format);
        Texture(u64 width, u64 height, u64 stride);
        Texture(u64 width, u64 height);
        ~Texture();
    };
}