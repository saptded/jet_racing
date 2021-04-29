//
// Created by Kseny
//

#include "viewerSource.hpp"
#include "utils.hpp"
#include "response.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cmath>

static void consoleLogFirst(std::string info){
    //std::cout << info << std::endl;
}


void ViewerSource::updateRacer(int id, ResponseRacer & respRacer) {
    racers[id].setPos(respRacer.points[0].x, respRacer.points[0].y);
    racers[id].setRot(respRacer.points);
    consoleLogFirst("updRacer");
}

void ViewerSource::updateDynamics(ResponseDynamicObjects & respObjects) {

}

void ViewerSource::createStage(std::vector<abstractElement>& elements) {
    consoleLogFirst("createStage in viewSource.cpp");
    stage++;
    tunnels.clear();
    dynamicObjects.clear();
    for (auto element: elements) {
        switch (element.type){
            case arc:
                tunnels.push_back(createArc(element));
            case line:
                tunnels.push_back(createLine(element));
        }
    }
}

void ViewerSource::createRacers(std::vector<ResponseRacer>& respRacers, sf::RenderWindow& window) {
//    if(!carIm.loadFromFile("../media/fire.png")){
//        consoleLogFirst("failed load image");
//    }
//    //car.loadFromImage(carIm);
//    car.loadFromFile("../media/fire.png");
    for (auto racer: respRacers){
        ViewerSourceRacer createdRacer = ViewerSourceRacer(racer.points);
        racers.push_back(createdRacer);
    }
    view = sf::View(window.getDefaultView());
    view.setCenter(respRacers[0].points[0].x, respRacers[0].points[0].y);
}

//void ViewerSource::updateCameraPos() {
//
//}

void ViewerSource::drawAll(sf::RenderWindow & window) {
    window.clear();
    racers[0].drawRacer(window);\
    //view.setCenter(racers[0].car.getPosition());
    window.display();
}
sf::VertexArray ViewerSource::createArc(abstractElement & arc) {
    sf::VertexArray sfarc;
    //
    //tunnels.push_back(sfarc);
    return sfarc;
}
sf::VertexArray ViewerSource::createLine(abstractElement & line) {
    sf::VertexArray sfline;
    //tunnels.push_back(sfline);
    return sfline;
}


