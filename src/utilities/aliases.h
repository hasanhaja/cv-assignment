//
// Created by Hasan on 13/03/20.
//

#ifndef CV_ASSIGNMENT_ALIASES_H
#define CV_ASSIGNMENT_ALIASES_H

#include <vector>
#include <string>
#include <map>
#include <opencv2/core/mat.hpp>

namespace util {
    using Data = std::vector<std::string>;
    /**
     * Structure
     * {
     *  train: hist_array
     *  ,
     *  empty: hist_array
     *
     * }
     */
    using Dataset = std::map<std::string, std::vector<cv::Mat>>;
}

#endif //CV_ASSIGNMENT_ALIASES_H
