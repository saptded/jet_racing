#pragma once

#include "response.hpp"
#include <memory>

class Observer {
 public:
    virtual void handleEvent(Response &response) = 0;
};

class Observable {
 public:
    virtual void notifyObserves(Response &response) = 0;
    virtual void addObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
};
