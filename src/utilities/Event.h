//
// Created by Hasan on 15/03/20.
//

#ifndef CV_ASSIGNMENT_EVENT_H
#define CV_ASSIGNMENT_EVENT_H

namespace util::output {
    /**
     * To translate this to the logic of the zones:
     * - If the vehicle is on Zone B, then entering or barrier
     *      - How to
     * - If the vehicle is on Zone B and A,  then on track.
     * - If the vehicle is on Zone A and C, then leaving.
     * - If the train is on Zone A, then train.
     * - If every zone is empty, then empty.
     */
    enum class Event {
        OnTrack,
        Entering,
        Barrier,
        Train,
        Leaving,
        Empty
    };

}


#endif //CV_ASSIGNMENT_EVENT_H
