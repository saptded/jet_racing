#pragma once

#include "mechanicalValues.hpp"
#include <memory>

class DrawableRacer;
struct Racer {
    Racer(Point point = {0, 0}, int id = 0);
    Racer(const Racer &racer) = default;
    Racer &operator=(const Racer &racer) = default;
    ~Racer() = default;

    float _width;
    float _height;

    float _rotation;
    Speed _speed;
    Speed _rotationSpeed;

    std::pair<Point, Point> _position;       // top left / bottom right
    std::pair<Point, Point> _positionExtra;  // bottom left / top right
    Point _center;
    Point _origin;

    uint8_t _id;

    std::tuple<bool, uint8_t> finished;

    bool onCollision;

    std::shared_ptr<DrawableRacer> _drObj;
};
