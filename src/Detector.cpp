//
// Created by Hasan on 13/03/20.
//

#include "Detector.h"

Detector::Detector() {

}

Detector::Detector(std::vector<Input> background, Input test_image) : background(std::move(background)), test_image(std::move(test_image)) { }

/**
 * This function is a placeholder and will change after initial testing.
 * TODO: Currently there is no error handling.
 */
void Detector::run() {
    detect();
}

/**
 * This function will run the detection process and set the result value to be returned.
 *
 * Reference: Majority of the code was copied from Lab 5 histogram_based_recognition_colour.cpp provided in the module
 */
void Detector::detect() {

    // TODO: placeholder. Refactor samples = background when refactor background name.
    std::vector<Input> samples = background;

    /** Detection logic starts */
    #define MAX_NUMBER_OF_SAMPLE_IMAGES 255
    int hist_size[] = {256, 256, 256};
    float range_0[] = {0, 255};
    const float* ranges[] = {range_0, range_0, range_0};
    int channels[] = {0, 1, 2};

    cv::MatND current_histogram;
    current_histogram.create(3, hist_size, CV_32F);

    cv::Mat input[MAX_NUMBER_OF_SAMPLE_IMAGES];
    cv::MatND histogram[MAX_NUMBER_OF_SAMPLE_IMAGES];


    //int sample_counter = 0;
    /**
     * Use the empty as a sample
     * Should work better with more samples.
     */

    // At the end of the for loop, the histograms of the samples should be collected and processed.
    for (int i = 0; i < samples.size(); i++) {
        // this should be the sample images
        input[i] = samples[i].image.clone();

        cv::calcHist(&samples[i].image, 1, channels, cv::Mat(), current_histogram, 3, hist_size, ranges, true, false);

        cv::normalize(current_histogram, current_histogram, 1, 0, cv::NORM_L1);

        histogram[i] = current_histogram.clone();
    }
    /** Compare with test image */
    cv::calcHist(&test_image.image, 1, channels, cv::Mat(), current_histogram, 3, hist_size, ranges, true, false);
    cv::normalize(current_histogram, current_histogram, 1, 0, cv::NORM_L1);

    double closest_distance = std::numeric_limits<double>::max();
    int closest_image = 0;

    for (int i = 0; i < samples.size(); i++) {
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


    this->debug_image = input[closest_image];
    // Since this gives you the closest image, that means you'll need to match up the name of the folder to then label the recognition. Then the event can be assigned on that basis.

    /** Detection logic ends */

    // Placeholder
    std::vector<std::string> events = {"1", "2", "3"};
    this->result = std::move(Result{"detector_test.png", events});
}

Result Detector::get_result() {
    return result;
}

void Detector::image_into_mat() {

}

cv::Mat Detector::debug_closest_image() {
    return debug_image;
}

Detector::~Detector() = default;
