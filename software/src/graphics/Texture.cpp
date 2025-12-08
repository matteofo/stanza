#include <graphics/Texture.hpp>

namespace stanza {
    u8 pixel_format_size(PixelFormat format) {
        switch (format) {
            case RGBA_32:
                return 4;
            case YUYV:
                return 2;
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

    u64 Texture::getPitch() {
        return this->pitch;
    }

    u64 Texture::getDepth() {
        return this->depth;
    }

    PixelFormat Texture::getFormat() {
        return this->format;
    }

    bool Texture::blit(void* source, u64 size) {
        if (source == NULL) {
            logger.error("Failed to blit!");
            return false;
        }

        memcpy(this->raw, source, size);

        return true;
    } 

    void Texture::setRaw(void* raw) {
        if (this->raw) free(this->raw);
        this->raw = raw;
    }

    Texture::Texture(u64 width, u64 height, PixelFormat format) : logger("Texture") {
        this->width = width;
        this->height = height;
        this->format = format;
        this->depth = pixel_format_size(RGBA_32);
        this->pitch = this->depth * width;

        this->raw = malloc(width * height * this->depth);
    }

    Texture::Texture(u64 width, u64 height, u64 depth) : logger("Texture") {
        this->width = width;
        this->height = height;
        this->format = OTHER;
        this->depth = depth;
        this->pitch = depth * width;
        
        this->raw = malloc(width * height * depth);
    }

    Texture::Texture(u64 width, u64 height) : logger("Texture") {
        this->width = width;
        this->height = height;
        this->format = RGBA_32;
        this->depth = pixel_format_size(RGBA_32);
        this->pitch = this->depth * width;

        this->raw = malloc(width * height * this->depth);
    }

    Texture::~Texture() {
        logger.warn("Deleting texture! {}", this->raw);
        free(this->raw);
    }
}
