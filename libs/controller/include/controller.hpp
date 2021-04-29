//
// Created by saptded on 15.04.2021.
//

#ifndef JET_RACING_LIBS_CONTROLLER_INCLUDE_CONTROLLER_HPP_
#define JET_RACING_LIBS_CONTROLLER_INCLUDE_CONTROLLER_HPP_

#include <SFML/Graphics.hpp>
#include "model.hpp"

class Controller : Observer {
 public:
    Controller(/*Server *server*/);
    ~Controller() = default;

    void startGame();
    void modelSettings();

 private:
    void handleEvent(ModelResponse &response) override;
    void handleButtonEvent();

    std::shared_ptr<Model> model;
    bool finishGame;
    sf::Window window;
};

#endif //JET_RACING_LIBS_CONTROLLER_INCLUDE_CONTROLLER_HPP_
