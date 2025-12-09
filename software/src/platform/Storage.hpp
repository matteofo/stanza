#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <linux/limits.h>
#include <turbojpeg.h>
#include <graphics/Texture.hpp>

namespace stanza {
    class Storage {
    public:
        static std::string getDCIMPath();
        static int getPictureNumber();
        static bool storeImage(Texture* image);

        static std::string getBasePath();
    };
}