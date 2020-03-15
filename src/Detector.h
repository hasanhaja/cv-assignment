//
// Created by Hasan on 13/03/20.
//

#ifndef CV_ASSIGNMENT_DETECTOR_H
#define CV_ASSIGNMENT_DETECTOR_H

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include "utilities/aliases.h"
#include "utilities/result.h"
#include "utilities/input.h"

using namespace util::output;
using namespace util::input;

class Detector {
private:
    /**
     * These are placeholders for initial testing.
     * File names are omitted.
     */
    //cv::Mat background, test_image;
    // Refactor background to sample
    std::vector<Input> background;
    Input test_image;
    Events events;
    Result result;

    void image_into_mat();
    void detect();

public:
    Detector();
    /**
     * This constructor is placeholder for initial testing of the histogram based recognition.
     * @param background
     * @param test_image
     */
    Detector(std::vector<Input> background, Input test_image);
    void run();
    Result get_result();
    ~Detector();
};


#endif //CV_ASSIGNMENT_DETECTOR_H
