#include <iostream>
#include <string>
#include <vector>
#include "utilities/display.h"
#include <filesystem>

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

    /**
     * Parse command line arguments into appropriate data structures
     */
    for (int i = 0; i < argc; i++) {
        std::filesystem::path file_path(argv[i]);
        filenames.push_back(file_path.filename().string());
    }

    std::cout << "File names read to vector" << std::endl;

    /**
     * Debug output of read file names
     * This will be useful for Output debug
     */
    for (auto file: filenames) {
        std::cout << file << std::endl;
    }



    /**
     * Placeholder for detection
     */
    std::string filename = "test.png";
    //std::vector<std::string> events = {"1", "2"};
    std::vector<std::string> events = {};

    util::display::debug(filename, events);

    /* End of placeholder */

    std::cout << "Program exited." << std::endl;

    return 0;
}
