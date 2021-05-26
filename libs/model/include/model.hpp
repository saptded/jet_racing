#pragma once

#include <list>
#include <memory>

#include "Map.h"
#include "abstractModel.hpp"
#include "observer.hpp"
#include "racer.hpp"
#include "racerController.hpp"
#include "menuInfo.hpp"
#include "../../webserver/src/lib/client/include/GameClient.hpp"

struct AbstractElement;

class Model : public AbstractModel {
public:
    Model() = delete;
    explicit Model(int id);
    explicit Model(std::shared_ptr<MenuInfo> menuInfo);
    ~Model();

    std::shared_ptr<MenuInfo> updateModel(Command &rotation) override;

private:
    Command _currentCommand{};

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

    std::shared_ptr<MenuInfo> menuInfo;
    std::shared_ptr<GameClient> _client;
};
