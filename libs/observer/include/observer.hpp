//
// Created by saptded on 15.04.2021.
//

#ifndef JET_RACING_LIBS_OBSERVER_INCLUDE_OBSERVER_HPP_
#define JET_RACING_LIBS_OBSERVER_INCLUDE_OBSERVER_HPP_

#include "modelResponse.hpp"

class Observer {
 public:
    virtual void handleEvent(ModelResponse &response) = 0;
};

class Observable {
 public:
    virtual void notifyObserves(ModelResponse &response) = 0;
    virtual void addObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
};

#endif //JET_RACING_LIBS_OBSERVER_INCLUDE_OBSERVER_HPP_
