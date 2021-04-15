//
// Created by saptded on 15.04.2021.
//

#ifndef JET_RACING_LIBS_CONTROLLER_INCLUDE_CONTROLLER_HPP_
#define JET_RACING_LIBS_CONTROLLER_INCLUDE_CONTROLLER_HPP_

#include "model.hpp"

class Controller : Observer {
 public:
    Controller(/*Server *server*/);
    ~Controller();

    void startGame(char *params);

 private:
    void handleEvent(ModelResponse *response) override;
    void handleButtonEvent();

    Model *model;
};

#endif //JET_RACING_LIBS_CONTROLLER_INCLUDE_CONTROLLER_HPP_
