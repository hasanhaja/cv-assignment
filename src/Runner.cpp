//
// Created by Hasan on 13/03/20.
//

#include "Runner.h"

Runner::Runner() {
    //detector = std::make_unique<Detector>();
}

Runner::Runner(Input input_images): input_images(std::move(input_images)) { }

void Runner::set_dataset(std::vector<Input> dataset) {
    this->dataset = std::move(dataset);
}

/**
 * This is also missing a lot of error handling currently.
 */
void Runner::run() {

    std::cout << "App run block entered" << std::endl;
    generate_histogram();

    // Need to ensure these things have been correctly initialized
//    detector = std::make_unique<Detector>(dataset, input_images);
    detector = std::make_unique<Detector>(input_images, histogram);

    //detector->set_histogram(histogram);

    detector->run();

    // TODO: Does this have to be a move?
    // As long as detector gets destroyed after this, it should be fine.
    this->_result = std::move(detector->get_result());
}

cv::Mat Runner::get_closest_image() {
    return detector->debug_closest_image();
}

void Runner::generate_histogram() {
    // TODO: placeholder. Refactor samples = background when refactor background name.
    //std::vector<Input> samples = dataset;

    /** Detection logic starts */
    #define MAX_NUMBER_OF_SAMPLE_IMAGES 255
    int hist_size[] = {256, 256, 256};
    float range_0[] = {0, 255};
    const float* ranges[] = {range_0, range_0, range_0};
    int channels[] = {0, 1, 2};

    cv::MatND current_histogram;
    current_histogram.create(3, hist_size, CV_32F);

    cv::Mat input[MAX_NUMBER_OF_SAMPLE_IMAGES];
    //cv::MatND histogram[MAX_NUMBER_OF_SAMPLE_IMAGES];

    // At the end of the for loop, the histograms of the samples should be collected and processed.
    for (int i = 0; i < dataset.size(); i++) {
        // this should be the sample images
        input[i] = dataset[i].image.clone();

        cv::calcHist(&dataset[i].image, 1, channels, cv::Mat(), current_histogram, 3, hist_size, ranges, true, false);

        cv::normalize(current_histogram, current_histogram, 1, 0, cv::NORM_L1);

        histogram[i] = current_histogram.clone();
    }

    //this->histogram = histogram;
}

Result Runner::result() {
    return _result;
}

Runner::~Runner() = default;
