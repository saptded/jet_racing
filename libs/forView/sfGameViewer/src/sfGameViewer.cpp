//
// Created by Kseny
//

#include "sfGameViewer.hpp"

#include "gameViewer.hpp"

void sfGameViewer::render(std::shared_ptr<Response> data) {
    {
        switch (data->eventType) {
            case RACER:
                renderRacer(data);
                break;
            case ENEMIES:
                renderEnemies(data);
                break;
            case STAGE:
                renderMap(data);
                break;
            case CHANGE_STAGE:
                increaseStage(data);
                break;
            case RENDER:
                displayWindow();
                break;
            case RESULTS:
                break;
        }

    }
}

sfGameViewer::sfGameViewer()
        : dist(sf::RenderWindow(sf::VideoMode(1920, 1080), "jet_racing")) {
    details = std::make_unique<sfViewerDetails>(1920, 1080);
}

void sfGameViewer::renderMap(std::shared_ptr<Response> data) {
    for (auto &elem : data.get()->stage.value()) {
        elem->draw(dist);
    }
}

void sfGameViewer::renderRacer(std::shared_ptr<Response> data) {
    data->racer->draw(dist);
    details->update(data->racer.value());
}

void sfGameViewer::displayWindow() { details->display(dist, stage); }

void sfGameViewer::renderEnemies(std::shared_ptr<Response> data) {
    for (auto racer : data->enemies.value()) {
        //if (racer.curStage == stage) {
            racer.draw(dist);
        //}
    }
}

void sfGameViewer::increaseStage(std::shared_ptr<Response> data) {
    if(data->curStage == 42){
        details->stop();
    }
    stage = data->curStage;
    for (auto elem : data->stage.value()) {
        elem->init(stage);
    }
}

Command sfGameViewer::handleButtonEvent() {
    sf::Event buttonEvent{};

    while (dist.pollEvent(buttonEvent)) {
        if (buttonEvent.type == sf::Event::Closed) {
            return Command::finish;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        return Command::left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return Command::right;
    }

    return Command::none;
}

void sfGameViewer::close() {
    dist.clear();
    dist.close();
}
