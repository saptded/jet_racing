#include <cmath>
#include <functional>

#include "AbstractElement.h"
#include "model.hpp"

Model::Model(int id)
    : _map(std::make_unique<Map>(std::string("../maps/stages.xml")))
    , _racer(_map->getStartPointByID(0), id)
    , currentStage(0)
    , finishedRacers(0){}

std::shared_ptr<MenuInfo> Model::updateModel(Command &rotation) {
    _currentCommand = rotation;

    updateMap();
    updateRacers();

    Response response = {ViewEvent::RENDER, std::nullopt, std::nullopt, std::nullopt};
    notifyObserves(response);

    return menuInfo;
}

void Model::addObserver(Observer *observer) { _observes.push_back(observer); }

void Model::removeObserver(Observer *observer) { _observes.remove(observer); }

void Model::notifyObserves(Response &response) {
    for (const auto &observer : _observes) {
        observer->handleEvent(response);
    }
}

Model::~Model() = default;

void Model::updateMap() {
    if(justStarted){
        Response response{ViewEvent::CHANGE_STAGE, std::nullopt, std::nullopt, std::make_optional(_map->getElementsInStage(currentStage))};
        notifyObserves(response);
        justStarted = false;
    }

    Response response{ViewEvent::STAGE, std::nullopt, std::nullopt, std::make_optional(_map->getElementsInStage(currentStage))};
    notifyObserves(response);
}

void Model::updateRacers() {
    updateRacer();
    updateEnemies();

    auto [isFinished, position] = _racer.finished;
    if (isFinished && position == 0) {
        _racer.finished = std::make_tuple(true, ++finishedRacers);
    }
    for (auto &enemy : enemies) {
        auto [isFinished, position] = enemy.finished;
        if (isFinished && position == 0) {
            enemy.finished = std::make_tuple(true, ++finishedRacers);
        }
    }
    if (finishedRacers == enemies.size() + 1) {
        menuInfo = std::make_shared<MenuInfo>();
        auto [isFinished, position] = _racer.finished;
        menuInfo->results[_racer._id] = position;
        for (auto &enemy : enemies) {
            auto [isEnemyFinished, enemyPosition] = enemy.finished;
            menuInfo->results.insert(std::make_pair(enemy._id, enemyPosition));
        }
    }
}

void Model::updateRacer() {

    auto element = _map->getCollisionElement(_racer._position.first, _racer._positionExtra.second, _racer._positionExtra.first, _racer._position.second, _racer._bottomCenter, currentStage);

    if (element != nullptr) {
        element->collision(_racer, _racerController, _currentCommand);
        if (_racer._teleport) {
            currentStage++;
            _racerController.updatePosition(_racer, _map->getStartPointByID(_racer._id));
            _racer._teleport = false;
            justStarted = true;
            _racerController.changeSpeed(_racer, true);
        }
    }

    _racerController.changeRotationSpeed(_currentCommand, _racer);
    _racerController.changeSpeed(_racer, false);

    _racerController.updateRotation(_racer);
    _racerController.updatePosition(_racer);

    Response response{ViewEvent::RACER, std::make_optional(_racer), std::nullopt, std::nullopt};
    notifyObserves(response);
}

void Model::updateEnemies() {}

Model::Model(const std::shared_ptr<MenuInfo>& menuInfo):
_map(std::make_unique<Map>(std::string("../maps/mapTest.xml")))
        , currentStage(0)
        , finishedRacers(0){
}
