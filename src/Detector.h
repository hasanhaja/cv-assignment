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

/**
 * Perhaps this class should only return one event per mask
 * And then Runner pools the results and performs the logic there.
 * Detector will loop through the entire dataset for every mask.
 * So three times the calculations since there will be three masks for three zones
 */
class Detector {
private:
    /**
     * These are placeholders for initial testing.
     * File names are omitted.
     */
    Input test_image;
    std::shared_ptr<util::Dataset> dataset;

    Result result;

    std::vector<cv::Mat> debug_histogram_input;
    cv::Mat debug_image;

    void detect(cv::Mat mask);

    Event calculate_event(std::map<std::string, double> difference_set);
    std::pair<std::string, double> calculate_min(std::map<std::string, double> difference_set);

public:
    Detector();
    Detector(Input test_image, std::shared_ptr<util::Dataset> dataset);
    //void set_histogram(cv::MatND histogram[]);
    cv::Mat debug_closest_image();

    /**
     * This is a little debugging backdoor. This won't be necessary for regular use API.
     * @param debug_histogram_input
     */
    void set_debug_histogram_input(std::vector<cv::Mat> debug_histogram_input);
    void run(cv::Mat mask);
    Result get_result();

    ~Detector();
};


#endif //CV_ASSIGNMENT_DETECTOR_H
