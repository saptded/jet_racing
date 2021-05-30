#pragma once

#include "response.hpp"
#include <iostream>
#include <optional>
#include <sfViewerDetails.hpp>

class Viewer {
public:
    Viewer();
    //explicit Viewer(Response &data);
    void render(Response &data) {
        switch (data.eventType) {
            case RACER: renderRacer(data); break;
            case ENEMIES: renderEnemies(data); break;
            case STAGE: renderMap(data); break;
            case CHANGE_STAGE: increaseStage(data); break;
            case RENDER: displayWindow(); break;
            case RESULTS: break;
        }

    };

    Command handleButtonEvent();
    void close();

private:
    void renderRacer(Response &data);
    void renderEnemies(Response &data);
    void renderMap(Response &data);
    void increaseStage(Response &data);
    void displayWindow();

    std::unique_ptr<sfViewerDetails> details;
    int stage = 0;

    sf::RenderWindow dist;
};
