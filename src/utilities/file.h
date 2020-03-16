//
// Created by Hasan on 16/03/20.
//

#ifndef CV_ASSIGNMENT_FILE_H
#define CV_ASSIGNMENT_FILE_H

#include <filesystem>
#include "aliases.h"

namespace util::file {

    util::Data get_image_filenames(const std::string& dir);

}

#endif //CV_ASSIGNMENT_FILE_H
