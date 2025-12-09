#include <platform/Storage.hpp>

namespace stanza {
    int Storage::getPictureNumber() {
        int number = 0;

        for (const auto& entry : std::filesystem::directory_iterator(Storage::getDCIMPath())) {
            if (!entry.is_regular_file()) continue;
            if (entry.path().extension() != ".jpeg" && entry.path().extension() != ".jpg") continue;
            
            std::string name = entry.path().filename().string();
            int pos = name.find(entry.path().extension(), 0);
            if (pos != std::string::npos) {
                name = name.substr(0, pos);
                int entryNum = std::stoi(name);
                if (entryNum >= number) {
                    number = entryNum;
                }
            } else {
                continue;
            }
        }

        return number + 1;
    }

    bool Storage::storeImage(Texture* image) {
        cv::Mat yuvImg(image->getWidth(), image->getHeight(), CV_8UC2, image->getRaw());
        cv::Mat bgrImg;
        cv::cvtColor(yuvImg, bgrImg, cv::COLOR_YUV2BGR_YUYV);

        u8* output = nullptr;
        u64 jpegSize = 0;

        tjhandle handle = tjInitCompress();
        if (handle == NULL) {
            return false;
        }

        int res = tjCompress2(
            handle, 
            bgrImg.data,
            image->getWidth(),
            image->getWidth() * 3,
            image->getHeight(),
            TJPF_BGR,
            &output,
            &jpegSize,
            TJSAMP_444,
            100,
            TJFLAG_ACCURATEDCT
        );

        if (res != 0) {
            return false;
        }
        
        std::ofstream file;
        std::string path = std::format("{}/{}.jpeg", Storage::getDCIMPath(), Storage::getPictureNumber());
        file.open(path, std::ios::binary);
        if (!file) {
            return false;
        }

        file.write((const char*) output, jpegSize);
        file.close();

        tjDestroy(handle);
        tjFree(output);

        yuvImg.release();
        bgrImg.release();

        return true;
    }

    std::string Storage::getBasePath() {
        char buf[PATH_MAX];
        getcwd(buf, PATH_MAX);

        std::string path;
        path.assign(buf);
        path += "/storage/";

        // create storage dir if it doesn't exist
        system(std::format("mkdir -p {}", path).c_str());

        return path;
    }

    std::string Storage::getDCIMPath() {
        std::string base = Storage::getBasePath();
        system(std::format("mkdir -p {}/DCIM", base).c_str());
        return base + "DCIM";
    }
}