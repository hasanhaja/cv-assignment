/**
 * @author Hasan Ali
 * @opencv_version 4.2.0 (currently installed on the development system)
 */
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "utilities/display.h"
#include "utilities/output.h"
#include "utilities/input.h"
#include "utilities/file.h"
#include "Runner.h"

#include <opencv2/opencv.hpp>

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
     * Runner aspect of the code
     */

    /**
     * Read sample images
     */
    /**
     * This could be done programmatically too, but it'll do for now.
     */
    std::vector<std::string> directory_names = {"barrier", "empty", "entering", "leaving", "ontrack", "train"};
    std::string root_dir = "../res/";
    std::string masks_dir = "masks";
    //util::Data images = util::file::get_image_filenames("../res/empty");

    /**
     * Data should folder names to all the sample files.
     * The Runner should hold all this information.
     */
    Runner app(test_images[0]);

    app.set_sample_dir(root_dir, directory_names);
    app.set_masks(masks_dir);

    //app.set_data_path(images);
    //app.set_dataset(dataset);

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
    util::output::Results results = app.results();
    std::cout << "App running complete." << std::endl;

    auto [filename, events] = results;

    /** END OF RUNNER*/

    util::display::debug(filename, events);

    /* End of placeholder */

    // The image can no longer be displayed

//    cv::namedWindow("Recognition result", 1);
//    cv::imshow("Recognition result", app.get_closest_image());
//    cv::waitKey(0);
//    cv::destroyWindow("Recognition result");

    std::cout << "Program exited." << std::endl;

    return 0;
}
