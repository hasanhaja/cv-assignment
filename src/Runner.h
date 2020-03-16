//
// Created by Hasan on 13/03/20.
//

#ifndef CV_ASSIGNMENT_RUNNER_H
#define CV_ASSIGNMENT_RUNNER_H

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <map>
#include <array>
#include <vector>

#include "utilities/aliases.h"
#include "utilities/input.h"
#include "utilities/output.h"
#include "utilities/file.h"
#include "Detector.h"

using namespace util::input;
using namespace util::output;

/**
 * TODO: The dataset path should be passed into Runner and runner should generate
 * the dataset in the appropriate format and process it
 */
class Runner {
private:
    std::string root_dir;
    std::vector<std::string> directory_names;

    /**
     * This map will contain all of the histograms per folder of images
     */
    util::Dataset data;
    // potentially use the transform function to manipulate the data

    Input input_images;
    std::unique_ptr<Detector> detector;

    /**
     * This is a little debugging backdoor.
     * This won't be necessary for regular use API.
     */
    //std::array<cv::Mat, 255> input;

    Results _results;
    // Given images (paths), this should work
    std::vector<Input> construct_mats(util::Data paths);
    util::Dataset construct_dataset();
    std::vector<cv::Mat> construct_histogram(const std::vector<Input>& dataset, const cv::Mat& mask);

    void verify_results();

public:
    Runner();
    explicit Runner(Input input_images);

    void set_sample_dir(std::string root_dir, std::vector<std::string> directory_names);
    void run();
    Results results();
    cv::Mat get_closest_image();
    ~Runner();
};


#endif //CV_ASSIGNMENT_RUNNER_H
