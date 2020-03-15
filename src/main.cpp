/**
 * @author Hasan Ali
 * @opencv_version 4.2.0 (currently installed on the development system)
 */
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "utilities/display.h"
#include "utilities/result.h"
#include "utilities/input.h"
#include "Runner.h"

#include <opencv2/imgcodecs.hpp>

/**
 * This main method will be the runner for the program
 * @return
 *
 * # TODO:
 * - Parse command line arguments
 * - Run a placeholder loop going through "images in the target file"
 * - Print debug message regarding status of progress
 * - Print debug message of detection
 */
int main(int argc, char *argv[]) {

    std::cout << "Hello, World! The program arguments are: " << std::endl;

    /**
     * This is just to debug all the arguments passed into the program.
     * This will be bundled and passed into the runner of the application
     */

    std::vector<std::string> filenames;
    std::vector<util::input::Input> test_images;

    /**
     * Command line arguments are test_images
     * Parse command line arguments into appropriate data structures
     */
    for (int i = 1; i < argc; i++) {
        std::filesystem::path file_path(argv[i]);
        filenames.push_back(file_path.string());
        //filenames.push_back(file_path.filename().string());
    }

    std::cout << "File names read to vector" << std::endl;

    /**
     * Debug output of read file names
     * This will be useful for Output debug
     */
    for (auto file: filenames) {
        std::cout << file << std::endl;

        cv::Mat file_mat = cv::imread(file);

        if (file_mat.empty()) {
            throw std::invalid_argument("Image not found or could not be opened.");
        }

        util::input::Input img {file, file_mat};

        test_images.push_back(img);

    }

    /**
     * Placeholder for detection
     */
    //std::string filename = "test.png";
    //std::vector<std::string> events = {"1", "2"};
    //std::vector<std::string> events = {};

    /**
     * Runner aspect of the code
     */

    /**
     * Read sample images
     */
    // TODO: Placeholder to represent files. Replace with file objs
    Data images;
    std::vector<util::input::Input> dataset;

    // TODO extract to function in own module
    for (auto& sample_path : std::filesystem::directory_iterator("../res/initial_test")) {
        auto path = sample_path.path().string();

        if (path.find(".png") != std::string::npos && path.find("test_") == std::string::npos) {
            images.push_back(sample_path.path().string());
        }
    }

    // Construct dataset
    for (auto image : images) {
        std::cout << "Image name: " << image << std::endl;

        cv::Mat img_mat = cv::imread(image);

        if (image.empty()) {
            throw std::invalid_argument("Could not open image.");
        }

        util::input::Input img {image, img_mat};

        dataset.push_back(img);
    }

    /**
     * Data should folder names to all the sample files.
     * The Runner should hold all this information.
     */

    Runner app(test_images[0]);

    app.set_dataset(dataset);

    std::cout << "Image_set initialized." << std::endl;
    /**
     * This can fail. There should be some error handling here.
     * Obviously, this should depend on the multithreading aspect of the app.
     */
    app.run();
    std::cout << "App running..." << std::endl;
    /*
     * TODO: This should be a map of events and the associated images.
     * Or something along those lines
    */
    util::output::Result results = app.result();
    std::cout << "App running complete." << std::endl;

    auto [filename, events] = results;

    /** END OF RUNNER*/

    util::display::debug(filename, events);

    /* End of placeholder */

    // TODO Debug: display the closest image

    std::cout << "Program exited." << std::endl;

    return 0;
}
