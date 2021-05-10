//
// Created by Kseny
//

#include "drawableArc.hpp"
#include <cmath>

static float getAngle(Point& rad, Point& center);
static float calcRadius(Point& one, Point& two);

void DrawableArc::draw(sf::RenderWindow &window) {
    window.draw(arcs);
}

void DrawableArc::create(abstractElement& element) {
    float radius = calcRadius(element.start, element.centre);
    if (radius != calcRadius(element.end, element.centre)){
        std::cout << "wrong arc radius = " << radius << std::endl;
        return;
    }
    float angleStart = getAngle(element.start, element.centre);
    float angleEnd = getAngle(element.end, element.centre);
    std::cout << angleStart << " " << angleEnd << std::endl;
    int vertexCount = (int)(radius);
    float angleStep = -std::fabs(angleEnd-angleStart)/(float)(vertexCount-1);
    std::cout << angleStep << std::endl;
    arcs = sf::VertexArray (sf::LineStrip, vertexCount);
    for (int i = 0; i < vertexCount; i++){
        arcs[i].position = sf::Vector2f(element.centre.x+radius*cosf(angleStart), element.centre.y+radius*sinf(angleStart));
        arcs[i].color = sf::Color::Black;
        if(i < 10){
            arcs[i].color = sf::Color::Red;
        } else if (i > vertexCount - 11){
            arcs[i].color = sf::Color::Blue;
        }
        angleStart+=angleStep;
    }
    std::cout << "arc " << element.centre.x << ", " << element.centre.y << " " << std::endl;
}

static float calcRadius(Point& one, Point& two){
    return sqrtf(powf(one.x-two.x, 2) + powf(one.y-two.y, 2));
}

static float getAngle(Point& rad, Point& center){
    float angle;
    if(rad.y - center.y == 0){
        if(rad.x > center.x){
            angle = 0;
        } else {
            angle = M_PI;
        }
        return angle;
    } else if (rad.x - center.x == 0){
        if(rad.y > center.y){
            angle = M_PI/2;
        } else {
            angle = -M_PI/2;
        }
        return angle;
    }
    angle = acosf((rad.x - center.x)/ calcRadius(rad, center));
    if (rad.y < center.y){
        angle = 2*M_PI-angle;
    }
    return angle;
}

