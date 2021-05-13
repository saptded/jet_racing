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

void DrawableArc::create(abstractElement& element, int stage) {
    sf::Color color = chooseColor.getWall(stage);
    float radius = calcRadius(element.start, element.centre);
    if (radius != calcRadius(element.end, element.centre)){
        std::cout << "wrong arc radius = " << radius << std::endl;
        return;
    }
    float angleStart = getAngle(element.centre, element.end); //поменято сознательно тк испраили направление
    float angleEnd = getAngle(element.centre, element.start);
    if (angleStart < angleEnd){
        angleStart += 2*M_PI;
    }
    std::cout << "arc " << element.centre.x << ", " << element.centre.y << " : angles st, e : ";
    std::cout << angleStart/M_PI*180 << " " << angleEnd/M_PI*180 << std::endl;
    int vertexCount = (int)(radius);
    float angleStep = (angleEnd-angleStart)/(float)(vertexCount-1);
    std::cout << " angleStep " << angleStep << std::endl;
    for(int j = -1; j <= 1; j++){
        float angle = angleStart;
        arcs[j+1] = sf::VertexArray (sf::LineStrip, vertexCount);
        for (int i = 0; i < vertexCount; i++){
            arcs[j+1][i].position = sf::Vector2f(element.centre.x-(radius+j*0.75)*cosf(angle), element.centre.y-(radius+j*0.75)*sinf(angle));
            arcs[j+1][i].color = color;
            angle+=angleStep;
        }
    }

}

float DrawableArc::calcRadius(Point& one, Point& two){
    return sqrtf(powf(one.x-two.x, 2) + powf(one.y-two.y, 2));
}

float DrawableArc::getAngle(Point&centre, Point&rad){
    float angle;
    if(centre.y - rad.y == 0){
        if(centre.x > rad.x){
            angle = 0;
        } else {
            angle = M_PI;
        }
        return angle;
    } else if (centre.x - rad.x == 0){
        if(centre.y < rad.y){
            angle = 3*M_PI/2;
        } else {
            angle = M_PI/2;
        }
        return angle;
    }
    angle = acosf((centre.x - rad.x)/ calcRadius(centre, rad));
    if (centre.y < rad.y){
        angle = 2*M_PI-angle;
    }
    return angle;
}

void DrawableLine::create(abstractElement& line, int stage) {
    sf::Color color = chooseColor.getWall(stage);
    // только для вертикальных и гозизонтальных линий
    if(line.end.y == line.start.y){
        for (int j = -1; j <= 1; j++){
            lines[j+1] = sf::VertexArray(sf::Lines, 2);
            lines[j+1][0].position = sf::Vector2f(line.start.x, line.start.y+j*0.75);
            lines[j+1][0].color = color;
            lines[j+1][1].position = sf::Vector2f(line.end.x, line.end.y+j*0.75);
            lines[j+1][1].color = color;
        }
    } else if (line.end.x == line.start.x) {
        for (int j = -1; j <= 1; j++){
            lines[j+1] = sf::VertexArray(sf::Lines, 2);
            lines[j+1][0].position = sf::Vector2f(line.start.x+j*0.75, line.start.y);
            lines[j+1][0].color = color;
            lines[j+1][1].position = sf::Vector2f(line.end.x+j*0.75, line.end.y);
            lines[j+1][1].color = color;
        }
    } else {
        // для остальных - некрасиво
        for (int j = -1; j <= 1; j++){
            lines[j+1] = sf::VertexArray(sf::Lines, 2);
            lines[j+1][0].position = sf::Vector2f(line.start.x+j*0.75, line.start.y);
            lines[j+1][0].color = sf::Color::Magenta;
            lines[j+1][1].position = sf::Vector2f(line.end.x+j*0.75, line.end.y);
            lines[j+1][1].color = sf::Color::Magenta;
        }
    }
}

void DrawableLine::draw(sf::RenderWindow &window) {
    for (auto line: lines){
        window.draw(line);
    }
}

void DrawablePortal::create(abstractElement &element, int stage) {
    rect.setSize(sf::Vector2f(element.start.x-element.end.x,element.start.y-element.end.y));
    rect.setPosition(element.end.x,element.end.y);
    rect.setFillColor(chooseColor.door);
}
void DrawablePortal::draw(sf::RenderWindow &window) {
    window.draw(rect);
}
void DrawableFinish::create(abstractElement &element, int stage) {}
void DrawableFinish::draw(sf::RenderWindow &window) {}
