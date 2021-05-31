#pragma once

#include "racer.hpp"
#include "racerController.hpp"

class Collisional {
public:
    virtual void collision(Racer &racer, RacerController &controller, Command command) = 0;
};
