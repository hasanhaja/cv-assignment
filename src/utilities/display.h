//
// Created by Hasan on 13/03/20.
//

#ifndef CV_ASSIGNMENT_DISPLAY_H
#define CV_ASSIGNMENT_DISPLAY_H

#include <string>
#include <iostream>
#include <vector>
#include "aliases.h"

namespace util::display {
    /**
     *
     * @param filename
     * @param event TODO: this can be a custom enum to represent event
     */
    void debug(const std::string& filename, const Events& events);
}

#endif //CV_ASSIGNMENT_DISPLAY_H
