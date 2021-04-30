#include "racer.hpp"

Racer::Racer(Point point)
    : _width(50)
    , _height(25)
    , _rotation(0)
    , _speed({0, 0})
    , _rotationSpeed({0, 0})
    , _position(std::pair<Point, Point>{point, {point.x + _width, point.y - _height}})
    , _center({3 * point.x + _width / 4, point.y + _height / 2}) {}
