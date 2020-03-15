//
// Created by Hasan on 15/03/20.
//

#ifndef CV_ASSIGNMENT_RESULT_H
#define CV_ASSIGNMENT_RESULT_H

#include "aliases.h"

/**
 * Result bundles the output so the filename and events get delivered together.
 */
namespace util::output {
    struct Result {
        std::string filename;
        Events events;
    };
}

#endif //CV_ASSIGNMENT_RESULT_H
