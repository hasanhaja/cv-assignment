//
// Created by Hasan on 13/03/20.
//

#ifndef CV_ASSIGNMENT_RUNNER_H
#define CV_ASSIGNMENT_RUNNER_H

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <map>
#include <array>

#include "utilities/aliases.h"
#include "utilities/input.h"
#include "utilities/result.h"
#include "Detector.h"

using namespace util::input;
using namespace util::output;

/**
 * TODO: The dataset path should be passed into Runner and runner should generate
 * the dataset in the appropriate format and process it
 */
class Runner {
private:
    /**
     * This might be deprecated in favour of Input
     */
    Data images;

    /**
     * This map will contain all of the histograms per folder of images
     */
    std::map<std::string, cv::MatND> data;
    /**
     * HistogramsFor case1, case2, ..., caseN;
     * void generate_sample_data();
     */
    std::array<cv::Mat, 255> histogram;
//    cv::MatND histogram[255];

    Input input_images;
    std::vector<Input> dataset;
    std::unique_ptr<Detector> detector;

    Result _result;

public:
    Runner();
    explicit Runner(Input input_images);
    void set_dataset(std::vector<Input> dataset);
    void generate_histogram();
    void run();
    Result result();
    cv::Mat get_closest_image();
    ~Runner();
};


#endif //CV_ASSIGNMENT_RUNNER_H
