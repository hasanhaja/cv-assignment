//
// Created by Hasan on 16/03/20.
//
#include "file.h"

namespace util::file {
    util::Data get_image_filenames(const std::string& dir) {
        util::Data images;
        for (auto& sample_path : std::filesystem::directory_iterator(dir)) {
            auto path = sample_path.path().string();

//            if (path.find(".png") != std::string::npos && path.find("test_") == std::string::npos) {
            if (path.find(".png") != std::string::npos) {
                images.push_back(sample_path.path().string());
            }
        }

        return images;
    }
}
