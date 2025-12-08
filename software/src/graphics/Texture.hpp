#pragma once
#include <iostream>
#include <vector>

#include <cstring>

#include <util/types.hpp>
#include <util/Logger.hpp>

namespace stanza {
    enum PixelFormat {
        OTHER,
        RGBA_32,
        YUYV
    };

    enum TextureFitMode {
        NORMAL,
        FILL,
        FIT
    };

    // returns the size (in bytes) of a pixel in the specified format
    u8 pixel_format_size(PixelFormat format);

    class Texture {
    protected:
        void* raw;
        u64 width, height, depth, pitch;
        PixelFormat format;
        Logger logger;
    public:
        void* getRaw();
        bool blit(void* source, u64 size);

        u64 getWidth();
        u64 getHeight();
        u64 getDepth();
        u64 getPitch();
        PixelFormat getFormat();

        void setRaw(void* raw);

        Texture(u64 width, u64 height, PixelFormat format);
        Texture(u64 width, u64 height, u64 depth);
        Texture(u64 width, u64 height);
        ~Texture();
    };
}