#include "racer.hpp"

Racer::Racer(Point point, int id)

    : _width(78)   // 30
    , _height(20)  // 12

    , _rotation(0)
    , _speed({0, 0})
    , _rotationSpeed({0, 0})
    , _position(std::pair<Point, Point>{point, {point.x + _width, point.y + _height}})
    , _positionExtra(std::pair<Point, Point>{{point.x, point.y + _height}, {point.x + _width, point.y}})
    , _center({point.x + 5 * _width / 6, point.y + _height / 2})
    , _origin({5 * _width / 6, _height / 2})
    , _id(id)
    , finished(false, 0)
    , onCollision(false) {}
