#include "racer.hpp"
#include "drawableRacer.hpp"

Racer::Racer(Point point, int id)

    : _width(100) // 30
    , _height(50) // 12

    , _rotation(0)
    , _speed({0, 0})
    , _rotationSpeed({0, 0})
    , _position(std::pair<Point, Point>{point, {point.x + _width, point.y + _height}})
    , _positionExtra(std::pair<Point, Point>{{point.x, point.y + _height}, {point.x + _width, point.y}})
    , _center({point.x + 5 * _width / 6, point.y + _height / 2})
    , _origin({5 * _width / 6, _height / 2})
    , _id(id)

    , _drObj(std::make_shared<DrawableRacer>(_width, _height, _origin, _id, _rotation)) {}

template <> void Racer::draw<sf::RenderWindow>(sf::RenderWindow &target) { _drObj->draw(*this, target); };
