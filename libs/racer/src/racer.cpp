#include "racer.hpp"

Racer::Racer(Point point)
    : _width(75)
    , _height(25)
    , _rotation(200)
    , _speed({0, 0})
    , _rotationSpeed({0, 0})
    , _position(std::pair<Point, Point>{point, {point.x + _width, point.y + _height}})
    , _center({point.x + 3 *_width / 4, point.y + _height / 2}) {}
