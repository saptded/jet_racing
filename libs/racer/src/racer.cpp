//
// Created by saptded on 15.04.2021.
//

#include "racer.hpp"

Racer::Racer() :
    rotation(0),
    speed({0, 0}),
    position(std::vector<Point>{{0, 0}, {1, 1}, {2, 2}}) {}

void Racer::updateRacerPosition(const std::vector<Point> &newPoints) {

}

void Racer::updateRacerRotation(RotationDirection rotationDirection) {
    if (rotationDirection == RotationDirection::left) {
        std::cout << "LEFT" << std::endl;
    }
    if (rotationDirection == RotationDirection::right) {
        std::cout << "RIGHT" << std::endl;
    }
    if (rotationDirection == RotationDirection::none) {
        std::cout << "NONE" << std::endl;
    }
}

void Racer::updateRacerSpeed(Speed addingSpeed) {

}

