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

        /**
         * If there aren't there masks, then this will throw exception.
         */
        //"barrier", "empty", "entering", "leaving", "ontrack", "train"
        if (dir_name == "train" || dir_name == "ontrack") {
            data[dir_name] = construct_histogram(input_images, masks.at(2).image);
        } else if (dir_name == "barrier" || dir_name == "entering") {
            data[dir_name] = construct_histogram(input_images, masks.at(0).image);
        } else if (dir_name == "leaving") {
            data[dir_name] = construct_histogram(input_images, masks.at(1).image);
        }else if (dir_name == "empty") {
            data[dir_name] = construct_histogram(input_images, cv::Mat());
        }
    }

    return data;
}

void Runner::set_masks(std::string masks_dir) {
    std::string image_dir = root_dir+masks_dir;
    util::Data image_paths = util::file::get_image_filenames(image_dir);

    auto raw_masks = construct_mats(image_paths);

    //std::cout << "Raw mask computed" << std::endl;

    std::vector<Input> converted;
    for (auto [filename, mat]: raw_masks) {
        mat.convertTo(mat, CV_8U, 1/256.0);
        /**
         * Masks are not working. Cannot convert from 16 bit to 8 bit
         */
        //std::cout << "Converted type: " << mat.type() << std::endl;
        //converted.push_back(Input{filename, mat});
        // Placeholder to short circuit Masks
        converted.push_back(Input{filename, cv::Mat()});
    }

    this->masks = converted;
}

std::vector<Input> Runner::construct_mats(util::Data paths) {

    std::vector<Input> dataset;

    for (auto image : paths) {

        cv::Mat img_mat = cv::imread(image);

        if (img_mat.empty()) {
            throw std::invalid_argument("Could not open image.");
        }
        //std::cout << "Image name: " << image << " Size: " << img_mat.size() << img_mat.type() << std::endl;

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
    Events events;
    std::string filename;
    for (auto [name, mask]: masks) {
        detector->run(mask);
        auto result = std::move(detector->get_result());
        events.push_back(result.event);
        if (filename.empty()) {
            filename = result.filename;
        }
    }

    this->_results = Results {filename, events};
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
