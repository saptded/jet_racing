//<<<<<<< HEAD
#include "racer.hpp"
#include "drawableRacer.hpp"

Racer::Racer(Point point, int id)
    : _width(125)
    , _height(50)
    , _rotation(200)
    , _speed({0, 0})
    , _rotationSpeed({0, 0})
    , _position(std::pair<Point, Point>{point, {point.x + _width, point.y + _height}})
    , _center({point.x + 5 * _width / 6, point.y + _height / 2})
    , _origin({5 * _width / 6, _height / 2})
    , _id(id)
    , _drObj(std::make_shared<DrawableRacer>(_width, _height, _id)) {}

template <> void Racer::draw<sf::RenderWindow>(sf::RenderWindow &target) { _drObj->draw(*this, target); };
