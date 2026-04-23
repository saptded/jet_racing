#pragma once

#include "response.hpp"
#include <memory>

class Observer {
public:
    virtual void handleEvent(std::shared_ptr<Response> response) = 0;
};

class Observable {
public:
    virtual void notifyObserves(std::shared_ptr<Response> response) = 0;
    virtual void addObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
};
