//
// Created by Kseny
//

#include "drawableObjects.hpp"
#include <cmath>
#include "sfColor.hpp"

static sfColor chooseColor;

static float getAngle(Point& rad, Point& center);
static float calcRadius(Point& one, Point& two);

void DrawableArc::draw(sf::RenderWindow &window) {
    for (auto arc: arcs){
        window.draw(arc);
    }
}
DrawableArc::DrawableArc(Point _start, Point _end, Point _center){
    start = _start;
    end = _end;
    center = _center;
        sf::Color color = chooseColor.getWall(1);
    float radius = calcRadius(start, center);
    if (radius != calcRadius(end, center)){
        std::cout << "wrong arc radius = " << radius << std::endl;
        return;
    }
    float angleStart = getAngle(center, end); //поменято сознательно тк испраили направление
    float angleEnd = getAngle(center, start);
    if (angleStart < angleEnd){
        angleStart += 2*M_PI;
    }
    std::cout << "arc " << center.x << ", " << center.y << " : angles st, e : ";
    std::cout << angleStart/M_PI*180 << " " << angleEnd/M_PI*180 << std::endl;
    int vertexCount = (int)(radius);
    float angleStep = (angleEnd-angleStart)/(float)(vertexCount-1);
    std::cout << " angleStep " << angleStep << std::endl;
    for(int j = -1; j <= 1; j++){
        float angle = angleStart;
        arcs[j+1] = sf::VertexArray (sf::LineStrip, vertexCount);
        for (int i = 0; i < vertexCount; i++){
            arcs[j+1][i].position = sf::Vector2f(center.x-(radius+j*0.75)*cosf(angle), center.y-(radius+j*0.75)*sinf(angle));
            arcs[j+1][i].color = color;
            angle+=angleStep;
        }
    }
}

float DrawableArc::calcRadius(Point& one, Point& two){
    return sqrtf(powf(one.x-two.x, 2) + powf(one.y-two.y, 2));
}

float DrawableArc::getAngle(Point&_center, Point&rad){
    float angle;
    if(_center.y - rad.y == 0){
        if(_center.x > rad.x){
            angle = 0;
        } else {
            angle = M_PI;
        }
        return angle;
    } else if (_center.x - rad.x == 0){
        if(_center.y < rad.y){
            angle = 3*M_PI/2;
        } else {
            angle = M_PI/2;
        }
        return angle;
    }
    angle = acosf((_center.x - rad.x)/ calcRadius(_center, rad));
    if (_center.y < rad.y){
        angle = 2*M_PI-angle;
    }
    return angle;
}

//void DrawableLine::create(AbstractElement& line, int stage) {
//     sf::Color color = chooseColor.getWall(stage);
//     // только для вертикальных и гозизонтальных линий
//     if(line._end.y == line._start.y){
//         for (int j = -1; j <= 1; j++){
//             lines[j+1] = sf::VertexArray(sf::Lines, 2);
//             lines[j+1][0].position = sf::Vector2f(line._start.x, line._start.y+j*0.75);
//             lines[j+1][0].color = color;
//             lines[j+1][1].position = sf::Vector2f(line._end.x, line._end.y+j*0.75);
//             lines[j+1][1].color = color;
//         }
//     } else if (line._end.x == line._start.x) {
//         for (int j = -1; j <= 1; j++){
//             lines[j+1] = sf::VertexArray(sf::Lines, 2);
//             lines[j+1][0].position = sf::Vector2f(line._start.x+j*0.75, line._start.y);
//             lines[j+1][0].color = color;
//             lines[j+1][1].position = sf::Vector2f(line._end.x+j*0.75, line._end.y);
//             lines[j+1][1].color = color;
//         }
//     } else {
//         // для остальных - некрасиво
//         for (int j = -1; j <= 1; j++){
//             lines[j+1] = sf::VertexArray(sf::Lines, 2);
//             lines[j+1][0].position = sf::Vector2f(line._start.x+j*0.75, line._start.y);
//             lines[j+1][0].color = sf::Color::Magenta;
//             lines[j+1][1].position = sf::Vector2f(line._end.x+j*0.75, line._end.y);
//             lines[j+1][1].color = sf::Color::Magenta;
//         }
//     }
//}

void DrawableLine::draw(sf::RenderWindow &window) {
    for (auto line: lines){
        window.draw(line);
    }
}
DrawableLine::DrawableLine(Point _start, Point _end, Point _center){
    start = _start;
    end = _end;
    center = _center;
    sf::Color color = chooseColor.getWall(1);
    // только для вертикальных и гозизонтальных линий
    if(end.y == start.y){
        for (int j = -1; j <= 1; j++){
            lines[j+1] = sf::VertexArray(sf::Lines, 2);
            lines[j+1][0].position = sf::Vector2f(start.x, start.y+j*0.75);
            lines[j+1][0].color = color;
            lines[j+1][1].position = sf::Vector2f(end.x, end.y+j*0.75);
            lines[j+1][1].color = color;
        }
    } else if (end.x == start.x) {
        for (int j = -1; j <= 1; j++){
            lines[j+1] = sf::VertexArray(sf::Lines, 2);
            lines[j+1][0].position = sf::Vector2f(start.x+j*0.75, start.y);
            lines[j+1][0].color = color;
            lines[j+1][1].position = sf::Vector2f(end.x+j*0.75, end.y);
            lines[j+1][1].color = color;
        }
    } else {
        // для остальных - некрасиво
        for (int j = -1; j <= 1; j++){
            lines[j+1] = sf::VertexArray(sf::Lines, 2);
            lines[j+1][0].position = sf::Vector2f(start.x+j*0.75, start.y);
            lines[j+1][0].color = sf::Color::Magenta;
            lines[j+1][1].position = sf::Vector2f(end.x+j*0.75, end.y);
            lines[j+1][1].color = sf::Color::Magenta;
        }
    }
}


//void DrawablePortal::create(AbstractElement &element, int stage) {
//    rect.setSize(sf::Vector2f(element._start.x-element._end.x,element._start.y-element._end.y));
//    rect.setPosition(element._end.x,element._end.y);
//    rect.setFillColor(chooseColor.door);
//}
//void DrawablePortal::draw(sf::RenderWindow &window) {
//    window.draw(rect);
//}
//void DrawableFinish::create(AbstractElement &element, int stage) {}
//void DrawableFinish::draw(sf::RenderWindow &window) {}
