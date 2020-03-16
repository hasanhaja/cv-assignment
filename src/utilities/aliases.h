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
     *  train: { filename1: hist1,
     *            filename2: hist2,
     *            ...
     *          }
     *  ,
     *  empty: { filename1: hist1,
     *            filename2: hist2,
     *            ...
     *          }
     *
     * }
     */
    using Dataset = std::map<std::string, std::map<std::string, cv::Mat>>;
}

#endif //CV_ASSIGNMENT_ALIASES_H
