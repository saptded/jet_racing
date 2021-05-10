//
// Created by Kseny
//

#include "viewerSource.hpp"
#include "utils.hpp"
#include "response.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>

static const float PI = 3.14159;

static void consoleLogFirst(std::string info){
    std::cout << info << std::endl;
}


void ViewerSource::updateRacer(int id, Racer & racer) {
    racers[id].setPos(racer._position);
    racers[id].setRot(racer._rotation);
}

void ViewerSource::updateDynamics(ResponseDynamicObjects & respObjects) {

}

void ViewerSource::createStage(std::vector<abstractElement>& elements) {
    consoleLogFirst("createStage in viewSource.cpp");
    stage++;
    walls.clear();
    dynamicObjects.clear();
    for (auto element: elements) {
        switch (element.type){
            case arcTime: {
                walls.push_back(createArc(element));
                break;
            }
            case arcNtime: {
                walls.push_back(createArc(element));
                break;
            }
            case line: {
                walls.push_back(createLine(element));
                break;
            }
        }
    }
}

void ViewerSource::createRacers(std::vector<Racer>& givenRacers,  sf::RenderWindow& window) {
    for (auto racer: givenRacers){
        ViewerSourceRacer createdRacer = ViewerSourceRacer(racer._width, racer._height, racer._id);
        racers.push_back(createdRacer);
    }
    view = sf::View(window.getDefaultView());
    view.setCenter(givenRacers[0]._position.first.x, givenRacers[0]._position.first.y);
}

//void ViewerSource::updateCameraPos() {
//
//}

void ViewerSource::drawAll(sf::RenderWindow & window) {
    window.clear(sf::Color::White);
    drawStage(window);
    for (auto racer: racers){ // итерация по вектору в обратном направлении
        racer.drawRacer(window);
    }
    //view.setCenter(racers[0].car.getPosition());
    window.display();
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
            angle = PI;
        }
        return angle;
    } else if (rad.x - center.x == 0){
        if(rad.y > center.y){
            angle = PI/2;
        } else {
            angle = -PI/2;
        }
        return angle;
    }
    angle = acosf((rad.x - center.x)/ calcRadius(rad, center));
    if (rad.y < center.y){
        std::cout << "angle from acos " << angle << std::endl;
        angle = 2*PI-angle;
    }
    return angle;
};

sf::VertexArray ViewerSource::createArc(abstractElement & arc) {
    float radius = calcRadius(arc.start, arc.centre);
    float angleStart = getAngle(arc.start, arc.centre);
    float angleEnd = getAngle(arc.end, arc.centre);
    int vertexCount = (int)(radius);
    float angleStep = (angleEnd-angleStart)/(float)(vertexCount-1);
    int k = 1;
    if(arc.type == arcTime){
        k = -1;
    }
    sf::VertexArray lines(sf::LineStrip, vertexCount);
    for (int i = 0; i < vertexCount; i++){
        lines[i].position = sf::Vector2f(arc.centre.x+radius*cos(angleStart), arc.centre.y+k*radius*sin(angleStart));
        lines[i].color = sf::Color::Black;
        angleStart+=angleStep;
    }
    std::cout << "arc " << arc.centre.x << ", " << arc.centre.y << " " << std::endl;
    return lines;
}
sf::VertexArray ViewerSource::createLine(abstractElement & line) {
    sf::VertexArray lines(sf::Lines, 2);
    lines[0].position = sf::Vector2f(line.start.x, line.start.y);
    lines[0].color = sf::Color::Black;
    lines[1].position = sf::Vector2f(line.end.x, line.end.y);
    lines[1].color = sf::Color::Black;
    return lines;
}
void ViewerSource::drawStage(sf::RenderWindow &window) {
    for (auto wall: walls){
        window.draw(wall);
    }
//    for (auto obj : dynamicObjects){
//        window.draw(obj);
//    }
}
