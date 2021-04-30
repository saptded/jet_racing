#pragma once

#include "mechanicalValues.hpp"

class Racer {
 public:
    explicit Racer(Point point = {0, 0});
    Racer(const Racer &racer) = default;

    Racer& operator=(const Racer &racer) = default;

    ~Racer() = default;

    double _width;
    double _height;

    double _rotation;
    Speed _speed;
    Speed _rotationSpeed;
    std::pair<Point, Point> _position;
    Point _center;
};
