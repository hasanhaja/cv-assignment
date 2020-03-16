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
    //Data images = util::file::get_image_filenames("../res/empty");
    for (auto dir_name: directory_names) {
        std::map<std::string, cv::Mat> image_map;
        std::string image_dir = root_dir+dir_name;
        util::Data image_paths = util::file::get_image_filenames(image_dir);
        // Populate image_map, and then append to data
        auto input_images = construct_mats(image_paths);

        for (auto [filename, img] : input_images) {
            image_map[filename] = img;
        }

        data[dir_name] = image_map;
    }

    return data;
}

std::vector<Input> Runner::construct_mats(util::Data paths) {

    std::vector<Input> dataset;

    for (auto image : paths) {
        std::cout << "Image name: " << image << std::endl;

        cv::Mat img_mat = cv::imread(image);

        if (img_mat.empty()) {
            throw std::invalid_argument("Could not open image.");
        }

        Input img {image, img_mat};

        dataset.push_back(img);
    }

    return dataset;
}

void Runner::set_data_path(util::Data paths) {
    this->paths = paths;
}

void Runner::set_sample_dir(std::string root_dir, std::vector<std::string> directory_names) {
    this->root_dir = root_dir;
    this->directory_names = directory_names;
}

void Runner::dataset_path(const std::vector<std::string>& folder_names) {

}

/**
 * This would become obsolete
 * @param dataset
 */
void Runner::set_dataset(std::vector<Input> dataset) {
    this->dataset = std::move(dataset);
}

/**
 * This is also missing a lot of error handling currently.
 */
void Runner::run() {

    std::cout << "App run block entered" << std::endl;
    this->dataset = construct_mats(this->paths);
    generate_histogram();

    // Need to ensure these things have been correctly initialized
    detector = std::make_unique<Detector>(input_images, dataset.size(), histogram);

    /**
     * This is a little debugging backdoor.
     * This won't be necessary for regular use API.
     */
    detector->set_debug_histogram_input(input);

    detector->run();

    // TODO: Does this have to be a move?
    // As long as detector gets destroyed after this, it should be fine.
    this->_result = std::move(detector->get_result());
}

cv::Mat Runner::get_closest_image() {
    return detector->debug_closest_image();
}

void Runner::generate_histogram() {

    int hist_size[] = {256, 256, 256};
    float range_0[] = {0, 255};
    const float* ranges[] = {range_0, range_0, range_0};
    int channels[] = {0, 1, 2};

    cv::Mat current_histogram;
    current_histogram.create(3, hist_size, CV_32F);

    /**
     * This is a little debugging backdoor.
     * This won't be necessary for regular use API.
     */
    //std::array<cv::Mat, 255> input;

    // At the end of the for loop, the histograms of the samples should be collected and processed.
    for (int i = 0; i < dataset.size(); i++) {
        // this should be the sample images
        input[i] = dataset[i].image.clone();

        cv::calcHist(&dataset[i].image, 1, channels, cv::Mat(), current_histogram, 3, hist_size, ranges, true, false);

        cv::normalize(current_histogram, current_histogram, 1, 0, cv::NORM_L1);

        histogram[i] = current_histogram.clone();
    }
}

/**
 * This should be the function that processes the results
 * @return
 */
Result Runner::result() {
    return _result;
}

Runner::~Runner() = default;
