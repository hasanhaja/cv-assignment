//
// Created by Hasan on 13/03/20.
//

#include "Detector.h"

Detector::Detector() { }

Detector::Detector(Input test_image, util::Dataset dataset): test_image(test_image), dataset(dataset) { }

/**
 * This function is a placeholder and will change after initial testing.
 * TODO: Currently there is no error handling.
 */
void Detector::run(cv::Mat mask) {
    detect(mask);
}

void Detector::set_debug_histogram_input(std::vector<cv::Mat> debug_histogram_input) {
    this->debug_histogram_input = debug_histogram_input;
}


/**
 * This function will run the detection process and set the result value to be returned.
 *
 * Reference: Majority of the code was copied from Lab 5 histogram_based_recognition_colour.cpp provided in the module
 */
void Detector::detect(cv::Mat mask) {

//    /** Detection logic starts */
    int hist_size[] = {256, 256, 256};
    float range_0[] = {0, 255};
    const float* ranges[] = {range_0, range_0, range_0};
    int channels[] = {0, 1, 2};

    cv::Mat current_histogram;
    current_histogram.create(3, hist_size, CV_32F);

    //std::array<cv::Mat, 255> input;

    /** Compare with test image */
    cv::calcHist(&test_image.image, 1, channels, mask, current_histogram, 3, hist_size, ranges, true, false);
    cv::normalize(current_histogram, current_histogram, 1, 0, cv::NORM_L1);

    double closest_distance = std::numeric_limits<double>::max();

    /**
     * Set up for entire dataset comparison
     */
    std::map<std::string, double> difference_set;

    for (auto data : dataset) {
        // data would be [label: histogram_array]
        auto [label, histogram] = data;
        for (int i = 0; i < histogram.size(); i++) {
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

            std::cout << std::endl;

            std::cout << "Comparison image " << i << "\nCorr: " << correlation << "\nChisq: " << chisq << "\nIntersect: " << intersect << "\nBhatt: " << bhat << "\nTotal distance = " << diff << std::endl;

            if (diff < closest_distance) {
                closest_distance = diff;
                difference_set[label] = closest_distance;
            }
        }
    }

    /** Detection logic ends */

    this->result = std::move(Result{test_image.filename, calculate_event(difference_set)});
}

/**
 * Calculate the minimum
 * @param difference_set
 * @return
 */
Event Detector::calculate_event(std::map<std::string, double> difference_set) {
    return Event::Empty;
}


Result Detector::get_result() {
    return result;
}

cv::Mat Detector::debug_closest_image() {
    return debug_image;
}

Detector::~Detector() = default;
