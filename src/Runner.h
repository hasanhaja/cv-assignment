//
// Created by Hasan on 13/03/20.
//

#ifndef CV_ASSIGNMENT_RUNNER_H
#define CV_ASSIGNMENT_RUNNER_H

#include <iostream>
#include <opencv2/core/mat.hpp>

#include "utilities/aliases.h"
#include "utilities/input.h"
#include "utilities/result.h"
#include "Detector.h"

using namespace util::input;
using namespace util::output;

/**
 * Use smart pointers
 * Should only hold names of images or the actual file, and not in the Mat format.
 */
class Runner {
private:
    /**
     * This might be deprecated in favour of Input
     */
    Data images;

    /**
     * HistogramsFor case1, case2, ..., caseN;
     * void generate_sample_data();
     */

    Input input_images;
    std::vector<Input> dataset;
    std::unique_ptr<Detector> detector;

    Result _result;

public:
    Runner();
    explicit Runner(Input input_images);
    void set_dataset(std::vector<Input> dataset);
    void image_set(const Data& images);
    void run();
    Result result();
    cv::Mat get_closest_image();
    ~Runner();
};


#endif //CV_ASSIGNMENT_RUNNER_H
