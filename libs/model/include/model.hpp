#pragma once
#include <list>
#include <memory>
#include "Map.h"
#include "abstractModel.hpp"
#include "observer.hpp"
#include "racer.hpp"
#include "racerController.hpp"
struct AbstractElement;
class Model : public AbstractModel {
public:
    explicit Model(int id);
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

    std::unique_ptr<Map> _map;
    Racer _racer;
    std::vector<Racer> enemies;

    RacerController _racerController;
    std::list<Observer *> _observes;

    uint8_t currentStage;
    uint8_t finishedRacers;
};