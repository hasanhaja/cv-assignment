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
    /**
     * This might be deprecated in favour of Input
     */
    util::Data paths;
    std::string root_dir;
    std::vector<std::string> directory_names;

    /**
     * This map will contain all of the histograms per folder of images
     */
    util::Dataset data, data_with_hist;
    // potentially use the transform function to manipulate the data

    /**
     * HistogramsFor case1, case2, ..., caseN;
     * void generate_sample_data();
     */
    std::array<cv::Mat, 255> histogram;

    Input input_images;
    std::vector<Input> dataset;
    std::unique_ptr<Detector> detector;

    /**
     * This is a little debugging backdoor.
     * This won't be necessary for regular use API.
     */
    std::array<cv::Mat, 255> input;

    Result _result;
    // Given images (paths), this should work
    std::vector<Input> construct_mats(util::Data paths);
    util::Dataset construct_dataset();

public:
    Runner();
    explicit Runner(Input input_images);

    /**
     * This is a placeholder. This should become set_dataset
     * @param paths
     */
    void set_data_path(util::Data paths);
    void set_sample_dir(std::string root_dir, std::vector<std::string> directory_names);
    void sample_dir_names(std::vector<std::string> directory_names);
    void dataset_path(const std::vector<std::string>& folder_names);
    void set_dataset(std::vector<Input> dataset);
    void generate_histogram();
    void run();
    Result result();
    cv::Mat get_closest_image();
    ~Runner();
};


#endif //CV_ASSIGNMENT_RUNNER_H
