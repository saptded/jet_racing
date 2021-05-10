//
// Created by saptded on 15.04.2021.
//

#include "racer.hpp"
Racer::Racer(Point point, int id) {

    _position = {point, point};
    _width = 120;
    _height = 40;
    _rotation = 0;
    _rotationSpeed = {0, 0};
    _speed = {0, 0};
    _center = {_width/4, _height/2};
    _origin = _origin;
    _id = id;
}
