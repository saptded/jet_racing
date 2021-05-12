//
// Created by Kseny
//

#include "viewer.hpp"

void Viewer::renderMap(Response &data, sf::RenderWindow &dist) {
    for (auto &elem : data.stage.value()) {
        elem->draw(dist);
    }
}