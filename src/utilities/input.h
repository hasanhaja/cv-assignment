//
// Created by Hasan on 15/03/20.
//

#ifndef CV_ASSIGNMENT_INPUT_H
#define CV_ASSIGNMENT_INPUT_H

#include <opencv2/core/mat.hpp>

namespace util::input {
    struct Input {
        std::string filename;
        cv::Mat image;
    };
}

#endif //CV_ASSIGNMENT_INPUT_H
