#include <graphics/Texture.hpp>

namespace stanza {
    int pixel_format_size(PixelFormat format) {
        switch (format) {
            case RGBA_32:
                return 4;
        }
    }

    void* Texture::getRaw() {
        return this->raw;
    }

    int Texture::getWidth() {
        return this->width;
    }

    int Texture::getHeight() {
        return this->height;
    }

    PixelFormat Texture::getFormat() {
        return this->format;
    }

    Texture::Texture(int width, int height, PixelFormat format) {
        this->width = width;
        this->height = height;
        this->format = format;

        this->raw = malloc(width * height * pixel_format_size(format));
    }

    Texture::Texture(int width, int height) {
        this->width = width;
        this->height = height;
        this->format = RGBA_32;

        this->raw = malloc(width * height * pixel_format_size(this->format));
    }

    Texture::~Texture() {
        free(this->raw);
    }
}
