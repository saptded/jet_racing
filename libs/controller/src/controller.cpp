//
// Created by saptded on 15.04.2021.
//

#include "controller.hpp"

Controller::Controller(/*server*/)
    : model(new Model(/*server*/)),
      finishGame(false),
      window(sf::Window(sf::VideoMode(1280, 720), "buttonEvents", sf::Style::Default)) {
}

void Controller::modelSettings() {
    std::vector<Observer *> obs;
    obs.push_back(this);
//    obs.push_back(View);

    model->setObserves(obs);
}

void Controller::startGame() {
    modelSettings();

    while (!finishGame) {
        handleButtonEvent();
    }
    window.close();
}

void Controller::handleEvent(ModelResponse &response) {
    if (response.event == Event::Finish) {
        finishGame = true;
    }
}

void Controller::handleButtonEvent() {
    sf::Event buttonEvent{};

    while (window.pollEvent(buttonEvent)) {
        if (buttonEvent.type == sf::Event::Closed) {
            finishGame = true;
        }
        if (buttonEvent.type == sf::Event::KeyPressed) {
            switch (buttonEvent.key.code) {
                case sf::Keyboard::Left: model->updateModel(RotationDirection::left);
                    break;
                case sf::Keyboard::Right: model->updateModel(RotationDirection::right);
                    break;
                case sf::Keyboard::Escape: finishGame = true;
                default: break;
            }
        } else {
            model->updateModel(RotationDirection::none);
        }
    }
}

