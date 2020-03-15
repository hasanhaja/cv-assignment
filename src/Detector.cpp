//
// Created by Hasan on 13/03/20.
//

#include "Detector.h"

Detector::Detector() { }

Detector::Detector(Input test_image, size_t dataset_length, std::array<cv::Mat, 255> histogram) : test_image(std::move(test_image)), dataset_length(std::move(dataset_length)), histogram(histogram) { }

/**
 * This function is a placeholder and will change after initial testing.
 * TODO: Currently there is no error handling.
 */
void Detector::run() {
    detect();
}

void Detector::set_debug_histogram_input(std::array<cv::Mat, 255> debug_histogram_input) {
    this->debug_histogram_input = debug_histogram_input;
}

/**
 * This function will run the detection process and set the result value to be returned.
 *
 * Reference: Majority of the code was copied from Lab 5 histogram_based_recognition_colour.cpp provided in the module
 */
void Detector::detect() {

//    /** Detection logic starts */
    int hist_size[] = {256, 256, 256};
    float range_0[] = {0, 255};
    const float* ranges[] = {range_0, range_0, range_0};
    int channels[] = {0, 1, 2};

    cv::Mat current_histogram;
    current_histogram.create(3, hist_size, CV_32F);

    //std::array<cv::Mat, 255> input;

    /** Compare with test image */
    cv::calcHist(&test_image.image, 1, channels, cv::Mat(), current_histogram, 3, hist_size, ranges, true, false);
    cv::normalize(current_histogram, current_histogram, 1, 0, cv::NORM_L1);

    double closest_distance = std::numeric_limits<double>::max();
    int closest_image = 0;

    for (int i = 0; i < dataset_length; i++) {
        /**
         * Histogram comparisons
         */
        double correlation = cv::compareHist(current_histogram, histogram[i], cv::HISTCMP_CORREL);
        double chisq = cv::compareHist(current_histogram, histogram[i], cv::HISTCMP_CHISQR);
        double intersect = cv::compareHist(current_histogram, histogram[i], cv::HISTCMP_INTERSECT);
        double bhat = cv::compareHist(current_histogram, histogram[i], cv::HISTCMP_BHATTACHARYYA);

        /**
         * Sum the differences as per lab 5
         * low corr = large diff (so invert)
         * low intersect = large diff (so invert)
         * high chisq = large diff
         * high bhat = large diff
         */

        double diff = (1 - correlation) + (1 - intersect) + chisq + bhat;

        std::cout << "Comparison image " << i << " Corr: " << correlation << " Chisq: " << chisq << " Intersect: " << intersect << " Bhatt: " << bhat << " Total distance = " << diff << std::endl;

        if (diff < closest_distance) {
            closest_distance = diff;
            closest_image = i;
        }

    }

    std::cout << "Closest image calculated." << std::endl;

    // TODO: For this to work, you'll need the same input array used to calculate hist
    // If I can tell which image it, then I solve the problem of finding where it belongs.
    this->debug_image = debug_histogram_input[closest_image];
    // Since this gives you the closest image, that means you'll need to match up the name of the folder to then label the recognition. Then the event can be assigned on that basis.

    /** Detection logic ends */

    // Placeholder
    std::vector<std::string> events = {"1", "2", "3"};
    this->result = std::move(Result{"detector_test.png", events});
}

//void Detector::set_histogram(cv::MatND generated[]) {
//    this->histogram = generated;
//}

Result Detector::get_result() {
    return result;
}

cv::Mat Detector::debug_closest_image() {
    return debug_image;
}

Detector::~Detector() = default;
