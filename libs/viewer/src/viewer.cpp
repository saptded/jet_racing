//
// Created by Kseny
//

#include "viewer.hpp"

Viewer::Viewer()
    : details(std::make_unique<sfViewerDetails>())
    , dist(sf::RenderWindow(sf::VideoMode(1920, 1080), "jet_racing")) {}

// Viewer::Viewer(sf::RenderWindow &dist) { details = std::make_shared<sfViewerDetails>(); }

// Viewer::Viewer() {  }

void Viewer::renderMap(Response &data) {
    for (auto &elem : data.stage.value()) {
        elem->draw(dist);
    }
}

void Viewer::renderRacer(Response &data) {
    data.racer->draw(dist);
    details->update(data.racer.value());
}

void Viewer::displayWindow() { details->display(dist, stage); }

void Viewer::renderEnemies(Response &data) {
    //    for (auto racer : data.enemies.value()) {
    //        racer.draw(dist);
    //    }
}

void Viewer::increaseStage(Response &data) {
    stage++;
    for (auto &elem : data.stage.value()) {
        elem->init(stage);
    }
}
Command Viewer::handleButtonEvent() {
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
void Viewer::close() {
    dist.clear();
    dist.close();
}

// void Viewer::initRender(Response &data, sf::RenderWindow &dist) {
//     details->init(data.racer.value(), dist);
// }
