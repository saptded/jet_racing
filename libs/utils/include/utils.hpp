//
// Created by saptded on 15.04.2021.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <memory>
#include <vector>

typedef struct Point {
    float x;
    float y;
    Point operator+(const Point& rv) const {
        return {x + rv.x,y + rv.y};
    }
    Point operator-(const Point& rv) const {
        return {x - rv.x,y - rv.y};
    }
} Point;



typedef struct Speed {
    int speedX;
    int speedY;
} Speed;

enum RotationDirection { left, right, none };

enum elementType {line, arcTime, arcNtime, notype}; //....

class DrawableObject;

class abstractElement {
public:
    Point start;
    Point end;
    Point centre;
    bool isDynamic = false;
    std::shared_ptr<DrawableObject> drObj;
    void createDrawable(int stage);
    template<typename M> void draw(M& target){};
};

//// если реализацию шаблонного метода вынести в отдельный файл, он не сможет слинковать
//// если оставить в этом, utils.hpp и drawableObject.hpp должны включать друг друга циклично
//// поэтому сделано как сделано...
//template<typename M>
//void abstractElement::draw(M& target){
//    if(isDynamic){
//        drObj2.draw(*this, target);
//    } else {
//        drObj2.draw(target);
//    }
//};




