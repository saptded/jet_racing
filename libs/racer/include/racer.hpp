//
// Created by saptded on 15.04.2021.
//

#ifndef JET_RACING_LIBS_RACER_INCLUDE_RACER_HPP_
#define JET_RACING_LIBS_RACER_INCLUDE_RACER_HPP_

#include "utils.hpp"

class Racer {
 public:
    Racer();
    ~Racer() = default;

    void updateRacerPosition(const std::vector<Point>& Points);
    void updateRacerRotation(RotationDirection addingRotation = RotationDirection::none);
    void updateRacerSpeed(Speed addingSpeed = Speed{0, 0});

 private:
    int rotation;
    Speed speed;
    std::vector<Point> position;
};

#endif //JET_RACING_LIBS_RACER_INCLUDE_RACER_HPP_
