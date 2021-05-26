//
// Created by Kseny
//

#pragma once

#include "response.hpp"
#include <iostream>
#include <optional>
#include <sfViewerDetails.hpp>

class Viewer {
public:
    Viewer() = delete;
    Viewer(Response &data, sf::RenderWindow & dist);
    //explicit Viewer(sf::RenderWindow &dist);
    void render(Response &data, sf::RenderWindow &dist) {
        switch (data.eventType) {
            case RACER: renderRacer(data, dist); break;
            case ENEMIES: renderEnemies(data, dist); break;
            case STAGE: renderMap(data, dist); break;
            case CHANGE_STAGE: increaseStage(data, dist); break;
            case RENDER: displayWindow(dist); break;
            case RESULTS: break;
        }
    };

private:
    void renderRacer(Response &data, sf::RenderWindow &dist);
    void renderEnemies(Response &data, sf::RenderWindow &dist);
    void renderMap(Response &data, sf::RenderWindow &dist);
    void increaseStage(Response &data, sf::RenderWindow &dist);
    void displayWindow(sf::RenderWindow &dist);

    std::shared_ptr<sfViewerDetails> details;
    int stage = 1;
};
