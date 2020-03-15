#include <iostream>
#include <string>
#include <vector>
#include "utilities/display.h"
#include "utilities/result.h"
#include <filesystem>
#include "Runner.h"

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
    //std::string filename = "test.png";
    //std::vector<std::string> events = {"1", "2"};
    //std::vector<std::string> events = {};

    /**
     * Runner aspect of the code
     */

    // TODO: Placeholder to represent files. Replace with file objs
    Data images;

    Runner app;

    app.image_set(images);

    /**
     * This can fail. There should be some error handling here.
     * Obviously, this should depend on the multithreading aspect of the app.
     */
    app.run();

    /*
     * TODO: This should be a map of events and the associated images.
     * Or something along those lines
    */
    util::output::Result results = app.result();

    auto [filename, events] = results;

    /** END OF RUNNER*/

    util::display::debug(filename, events);

    /* End of placeholder */

    std::cout << "Program exited." << std::endl;

    return 0;
}
