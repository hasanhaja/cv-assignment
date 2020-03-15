//
// Created by Hasan on 13/03/20.
//

#include "Detector.h"

Detector::Detector() {

}

Detector::Detector(Input background, Input test_image) : background(std::move(background)), test_image(std::move(test_image)) { }

/**
 * This function is a placeholder and will change after initial testing
 */
void Detector::run() {

}

Result Detector::get_result() {
    std::vector<std::string> events = {"1", "2"};

    return Result{"test.png", events};
}

void Detector::image_into_mat() {

}

Detector::~Detector() = default;
