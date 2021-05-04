#pragma once

#include <list>
#include <memory>

#include "abstractModel.hpp"
#include "observer.hpp"
#include "racer.hpp"
#include "racerController.hpp"

struct AbstractElement;

class Model : public AbstractModel {
public:
    Model();
    ~Model();

    void updateModel(Rotation &rotation) override;

private:
    Rotation _currentCommand{};

    void addObserver(Observer *observer) override;
    void removeObserver(Observer *observer) override;
    void notifyObserves(Response &response) override;

    void updateMap();
    void updateRacers();

    void updateRacer();
    void updateEnemies();

    void onCollision(const AbstractElement& element);

    Racer _racer;
    RacerController _racerController;
    //    Map *map;
    //    Server *server

    std::list<Observer *> _observes;
};
