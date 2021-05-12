//<<<<<<< HEAD
#include "racer.hpp"

Racer::Racer(Point point, int id)
    : _width(125)
    , _height(50)
    , _rotation(200)
    , _speed({0, 0})
    , _rotationSpeed({0, 0})
    , _position(std::pair<Point, Point>{point, {point.x + _width, point.y + _height}})
    , _center({point.x + 5 * _width / 6, point.y + _height / 2})
    , _origin({5 * _width / 6, _height / 2}) {}
//=======
////
//// Created by saptded on 15.04.2021.
////
//
//#include "racer.hpp"
//#include "drawableRacer.hpp"
//
//Racer::Racer(Point point, int id) {
//
//    _position = {point, point};
//    _width = 120;
//    _height = 40;
//    _rotation = 0;
//    _rotationSpeed = {0, 0};
//    _speed = {45, 150};
//    _center = {_width/4, _height/2};
//    _origin;
//    _id = id;
//}
//
//void Racer::createDrawable(){
//    drObj = std::make_shared<DrawableRacer>();
//    drObj->create(*this);
//};
//
//template<>
//void Racer::draw<sf::RenderWindow>(sf::RenderWindow& target){
//    drObj->draw(*this, target);
//};
//>>>>>>> view_kseny
