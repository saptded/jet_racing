//
// Created by saptded on 15.04.2021.
//

#ifndef JET_RACING_LIBS_RACER_INCLUDE_RACER_HPP_
#define JET_RACING_LIBS_RACER_INCLUDE_RACER_HPP_

#include "utils.hpp"

class Racer {
 public:
    void updateRacerPosition();
    void updateRacerRotation(RotationDirection addingRotation = RotationDirection::none);
    void updateRacerSpeed(Speed addingSpeed = Speed{0, 0});

 private:
    int rotation;
    Speed speed;
    Point position[3];
};

#endif //JET_RACING_LIBS_RACER_INCLUDE_RACER_HPP_
