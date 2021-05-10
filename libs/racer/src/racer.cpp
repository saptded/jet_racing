#include "racer.hpp"

Racer::Racer(Point point)
    : _width(125)
    , _height(50)
    , _rotation(200)
    , _speed({0, 0})
    , _rotationSpeed({0, 0})
    , _position(std::pair<Point, Point>{point, {point.x + _width, point.y + _height}})
    , _center({point.x + 5 * _width / 6, point.y + _height / 2})
    , _origin({5 * _width / 6, _height / 2}) {}
