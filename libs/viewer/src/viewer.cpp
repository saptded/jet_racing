//
// Created by Kseny
//

#include "viewer.hpp"

Viewer::Viewer(sf::RenderWindow &dist) {
    details = std::make_shared<sfViewerDetails>(dist);
}

Viewer::Viewer() {
    details = std::make_shared<sfViewerDetails>();
}

void Viewer::renderMap(Response &data, sf::RenderWindow& dist) {
    for (auto &elem : data.stage.value()) {
        elem->draw(dist);
    }
}

void Viewer::renderRacer(Response &data, sf::RenderWindow& dist) {
    data.racer->draw(dist);
    //details->update(data.racer.value());
}

void Viewer::displayWindow(sf::RenderWindow &dist) {
    details->display(dist, 1);
}

//void Viewer::initRender(Response &data, sf::RenderWindow &dist) {
//    details->init(data.racer.value(), dist);
//}
