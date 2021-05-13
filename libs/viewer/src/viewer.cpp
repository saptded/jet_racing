//
// Created by Kseny
//

#include "viewer.hpp"

void Viewer::renderMap(Response &data, sf::RenderWindow &dist) {
    for (auto &elem : data.stage.value()) {
        elem->draw(dist);
    }
}
void Viewer::displayWindow(sf::RenderWindow &dist) { details->display(dist, 1); }
Viewer::Viewer() { details = std::make_shared<sfViewerDetails>(); }
void Viewer::renderRacer(Response &data, sf::RenderWindow &dist) { data.racer->draw(dist); }
