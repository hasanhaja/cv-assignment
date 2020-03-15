//
// Created by Hasan on 13/03/20.
//

#ifndef CV_ASSIGNMENT_RUNNER_H
#define CV_ASSIGNMENT_RUNNER_H

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
    Input input_images, dataset;
    std::unique_ptr<Detector> detector;

    Result _result;

public:
    Runner();
    explicit Runner(Input input_images);
    void set_dataset(Input dataset);
    void image_set(const Data& images);
    void run();
    Result result();
    ~Runner();
};


#endif //CV_ASSIGNMENT_RUNNER_H
