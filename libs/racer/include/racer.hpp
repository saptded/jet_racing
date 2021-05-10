//
// Created by saptded on 15.04.2021.
//

#pragma once

#include "utils.hpp"

struct Racer {
    explicit Racer(Point point = {0, 0}, int id = 0);
    Racer(const Racer &racer) = default;
    Racer &operator=(const Racer &racer) = default;
    ~Racer() = default;

    float _width;
    float _height;

    float _rotation;
    Speed _speed;
    Speed _rotationSpeed;
    std::pair<Point, Point> _position;
    Point _center;
    Point _origin;

    int _id;
};
