//
// Created by Kseny
//

#include "viewer.hpp"

Viewer::Viewer(Response &data, sf::RenderWindow &dist):
details(std::make_unique<sfViewerDetails>())
{
    for (auto &elem : data.stage.value()) {
        elem->init(data.curStage);
    }
}

// Viewer::Viewer(sf::RenderWindow &dist) { details = std::make_shared<sfViewerDetails>(); }

//Viewer::Viewer() {  }

void Viewer::renderMap(Response &data, sf::RenderWindow &dist) {
    for (auto &elem : data.stage.value()) {
        elem->draw(dist);
    }
}

void Viewer::renderRacer(Response &data, sf::RenderWindow &dist) {
    data.racer->draw(dist);
    details->update(data.racer.value());
}

void Viewer::displayWindow(sf::RenderWindow &dist) { details->display(dist, stage); }

void Viewer::renderEnemies(Response &data, sf::RenderWindow &dist) {
//    for (auto racer : data.enemies.value()) {
//        racer.draw(dist);
//    }
}

void Viewer::increaseStage(Response &data, sf::RenderWindow &dist) {
    stage++;
    for (auto &elem : data.stage.value()) {
        elem->init(stage);
    }
}

// void Viewer::initRender(Response &data, sf::RenderWindow &dist) {
//     details->init(data.racer.value(), dist);
// }
