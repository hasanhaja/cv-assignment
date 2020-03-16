//
// Created by Hasan on 13/03/20.
//

#include "Runner.h"

Runner::Runner() {
    //detector = std::make_unique<Detector>();
}

Runner::Runner(Input input_images): input_images(std::move(input_images)) { }

util::Dataset Runner::construct_dataset() {
    util::Dataset data;
    
    for (auto dir_name: directory_names) {
        std::string image_dir = root_dir+dir_name;
        util::Data image_paths = util::file::get_image_filenames(image_dir);

        auto input_images = construct_mats(image_paths);

        data[dir_name] = construct_histogram(input_images, cv::Mat());
    }

    return data;
}

std::vector<Input> Runner::construct_mats(util::Data paths) {

    std::vector<Input> dataset;

    for (auto image : paths) {
        //std::cout << "Image name: " << image << std::endl;

        cv::Mat img_mat = cv::imread(image);

        if (img_mat.empty()) {
            throw std::invalid_argument("Could not open image.");
        }

        Input img {image, img_mat};

        dataset.push_back(img);
    }

    return dataset;
}

void Runner::set_sample_dir(std::string root_dir, std::vector<std::string> directory_names) {
    this->root_dir = root_dir;
    this->directory_names = directory_names;
}


/**
 * This is also missing a lot of error handling currently.
 */
void Runner::run() {

    std::cout << "App run block entered" << std::endl;
//    this->dataset = construct_mats(this->paths);
//    construct_histogram(dataset, cv::Mat());

    data = std::make_shared<util::Dataset>(construct_dataset());
    // Need to ensure these things have been correctly initialized
    detector = std::make_unique<Detector>(input_images, data);

    /**
     * This is a little debugging backdoor.
     * This won't be necessary for regular use API.
     */
    //detector->set_debug_histogram_input(input);

    /**
     * Iterate through different masks and get Results
     */
    detector->run(cv::Mat());

    // TODO: Does this have to be a move?
    // As long as detector gets destroyed after this, it should be fine.
    auto result = std::move(detector->get_result());
    Events events = {result.event};
    this->_results = Results {result.filename, events};
}

cv::Mat Runner::get_closest_image() {
    return detector->debug_closest_image();
}

std::vector<cv::Mat> Runner::construct_histogram(const std::vector<Input>& dataset, const cv::Mat& mask) {
    std::vector<cv::Mat> histogram;


    int hist_size[] = {256, 256, 256};
    float range_0[] = {0, 255};
    const float* ranges[] = {range_0, range_0, range_0};
    int channels[] = {0, 1, 2};

    cv::Mat current_histogram;
    current_histogram.create(3, hist_size, CV_32F);

    // At the end of the for loop, the histograms of the samples should be collected and processed.
    for (int i = 0; i < dataset.size(); i++) {
        cv::calcHist(&dataset[i].image, 1, channels, mask, current_histogram, 3, hist_size, ranges, true, false);

        cv::normalize(current_histogram, current_histogram, 1, 0, cv::NORM_L1);

        //histogram[i] = current_histogram.clone();
        histogram.push_back(current_histogram.clone());
    }

    return histogram;
}

/**
 * This should be the function that processes the results
 * @return
 */
Results Runner::results() {
    return _results;
}

Runner::~Runner() = default;
