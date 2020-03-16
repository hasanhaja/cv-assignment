//
// Created by Hasan on 15/03/20.
//

#ifndef CV_ASSIGNMENT_OUTPUT_H
#define CV_ASSIGNMENT_OUTPUT_H

#include "Event.h"

/**
 * Result bundles the output so the filename and events get delivered together.
 */
namespace util::output {
    using Events = std::vector<Event>;
    struct Result {
        std::string filename;
        Events events;
    };

}

#endif //CV_ASSIGNMENT_OUTPUT_H
