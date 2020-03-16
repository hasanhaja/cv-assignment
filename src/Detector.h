//
// Created by Hasan on 13/03/20.
//

#ifndef CV_ASSIGNMENT_DETECTOR_H
#define CV_ASSIGNMENT_DETECTOR_H

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <array>
#include "utilities/aliases.h"
#include "utilities/output.h"
#include "utilities/input.h"

using namespace util::output;
using namespace util::input;

class Detector {
private:
    /**
     * These are placeholders for initial testing.
     * File names are omitted.
     */
    Input test_image;
    //Events events;
    Events events;
    Result result;

    size_t dataset_length;
    std::array<cv::Mat, 255> histogram;

    std::array<cv::Mat, 255> debug_histogram_input;

    cv::Mat debug_image;
    void detect();

public:
    Detector();
    Detector(Input test_image, size_t dataset_length, std::array<cv::Mat, 255> histogram);
    //void set_histogram(cv::MatND histogram[]);
    cv::Mat debug_closest_image();

    /**
     * This is a little debugging backdoor. This won't be necessary for regular use API.
     * @param debug_histogram_input
     */
    void set_debug_histogram_input(std::array<cv::Mat, 255> debug_histogram_input);
    void run();
    Result get_result();

    ~Detector();
};


#endif //CV_ASSIGNMENT_DETECTOR_H
