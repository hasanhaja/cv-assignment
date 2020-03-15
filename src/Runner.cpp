//
// Created by Hasan on 13/03/20.
//

#include "Runner.h"

Runner::Runner() {
    //detector = std::make_unique<Detector>();
}

Runner::Runner(Input input_images): input_images(std::move(input_images)) { }

void Runner::set_dataset(Input dataset) {
    this->dataset = std::move(dataset);
}

void Runner::image_set(const Data& images) {
    /**
     * The function that sets the image values in detector should trigger then image_into_mat() private function
     */
    //detector->image_into_mat();
}

/**
 * This is also missing a lot of error handling currently.
 */
void Runner::run() {
    detector = std::make_unique<Detector>(dataset, input_images);

    detector->run();

    // TODO: Does this have to be a move?
    // As long as detector gets destroyed after this, it should be fine.
    this->_result = std::move(detector->get_result());
}

Result Runner::result() {
    return _result;
}

Runner::~Runner() = default;
