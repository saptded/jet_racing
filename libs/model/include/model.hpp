
//
// Created by saptded on 15.04.2021.
//

#ifndef JET_RACING_LIBS_MODEL_INCLUDE_MODEL_HPP_
#define JET_RACING_LIBS_MODEL_INCLUDE_MODEL_HPP_

#include "racer.hpp"
#include "observer.hpp"

class Model : Observable {
 public:
    Model(/*Server *server*/);
    ~Model();

    void updateModel();

 private:
    void updateMap();
    void updateRacers();

    void updateRacer();
    void updateEnemies();

    void notifyObserves(ModelResponse *response) override;
    void addObserver(Observer observer) override; // ?
    void removeObserver(Observer observer) override; // ?


    Racer *racer;
//    Map *map;
//    Server *server

    Observer *observes;
};

#endif //JET_RACING_LIBS_MODEL_INCLUDE_MODEL_HPP_
