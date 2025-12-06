#include <graphics/Texture.hpp>

namespace stanza {
    u8 pixel_format_size(PixelFormat format) {
        switch (format) {
            case RGBA_32:
                return 4;
        }
    }

    void* Texture::getRaw() {
        return this->raw;
    }

    u64 Texture::getWidth() {
        return this->width;
    }

    u64 Texture::getHeight() {
        return this->height;
    }

    u64 Texture::getStride() {
        return this->stride;
    }

    PixelFormat Texture::getFormat() {
        return this->format;
    }

    Texture::Texture(u64 width, u64 height, PixelFormat format) {
        this->width = width;
        this->height = height;
        this->format = format;
        this->stride = pixel_format_size(format);

        this->raw = malloc(width * height * this->stride);
    }

    Texture::Texture(u64 width, u64 height, u64 stride) {
        this->width = width;
        this->height = height;
        this->format = OTHER;
        this->stride = stride;
        
        this->raw = malloc(width * height * stride);
    }

    Texture::Texture(u64 width, u64 height) {
        this->width = width;
        this->height = height;
        this->format = RGBA_32;
        this->stride = pixel_format_size(RGBA_32);

        this->raw = malloc(width * height * this->stride);
    }

    Texture::~Texture() {
        free(this->raw);
    }
}
