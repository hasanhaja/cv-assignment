//
// Created by Hasan on 13/03/20.
//

#include "display.h"

namespace util::display {
    void debug(const std::string& filename, const Events& events) {
        std::cout << filename << ": ";

        if (events.empty()) {
            std::cout << "0";
        } else {
            for (const auto& event: events) {
                 std::cout << "event " << event << " ";
            }
        }

        std::cout<< std::endl;
    }
}
