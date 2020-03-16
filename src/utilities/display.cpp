//
// Created by Hasan on 13/03/20.
//

#include "display.h"

namespace util::display {

    std::string event_string(const util::output::Event& event) {
        std::string name;

        switch (event) {
            case output::Event::OnTrack:
                name = "OnTrack";
                break;
            case output::Event::Entering:
                name = "Entering";
                break;
            case output::Event::Barrier:
                name = "Barrier";
                break;
            case output::Event::Train:
                name = "Train";
                break;
            case output::Event::Leaving:
                name = "Leaving";
                break;
            case output::Event::Empty:
                name = "Empty";
                break;
        }

        return name;
    }

    void debug(const std::string& filename, const util::output::Events& events) {
        std::cout << filename << ": ";

        if (events.empty()) {
            std::cout << "0";
        } else {
            for (const auto& event: events) {
                std::cout << "event " << event_string(event) << " ";
            }
        }

        std::cout<< std::endl;
    }
}
