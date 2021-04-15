
//
// Created by saptded on 15.04.2021.
//

#ifndef JET_RACING_LIBS_MODEL_INCLUDE_MODEL_HPP_
#define JET_RACING_LIBS_MODEL_INCLUDE_MODEL_HPP_

#include <memory>
#include <list>

#include "racer.hpp"
#include "observer.hpp"

class Model : Observable {
 public:
    Model(/*Server *server*/);
    ~Model();

    void updateModel(RotationDirection &&rotationDirection);
    void setObserves(const std::vector<Observer*>& obs);

 private:
    void updateMap();
    void updateRacers(RotationDirection &rotationDirection);

    void updateRacer(RotationDirection &rotationDirection);
    void updateEnemies();

    void notifyObserves(ModelResponse &response) override;
    void addObserver(Observer *observer) override; // ?
    void removeObserver(Observer *observer) override; // ?


    Racer racer;
//    Map *map;
//    Server *server

    std::list<Observer*> observes;
};

#endif //JET_RACING_LIBS_MODEL_INCLUDE_MODEL_HPP_
