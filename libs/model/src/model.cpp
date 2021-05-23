#include <cmath>
#include <functional>

#include "AbstractElement.h"
#include "model.hpp"

Model::Model(int id)
    : _map(std::make_unique<Map>(std::string("../maps/mapTest.xml"))), _racer(_map->getStartPointByID(0).first, id), currentStage(0), finishedRacers(0) {}

void Model::updateModel(Rotation &rotation) {
    _currentCommand = rotation;

    updateMap();
    updateRacers();

    Response response = {ViewEvent::RENDER, std::nullopt, std::nullopt, std::nullopt};
    notifyObserves(response);
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

    Response response{ViewEvent::STAGE, std::nullopt, std::nullopt, std::make_optional(_map->getElementsInStage(currentStage))};
    notifyObserves(response);
}

void Model::updateRacers() {
    updateRacer();
    updateEnemies();

    auto [isFinished, position] = _racer.finished;
    if (isFinished) {
        _racer.finished = std::make_tuple(true, ++finishedRacers);
    }
    for (auto &enemy : enemies) {
        auto [isFinished, position] = enemy.finished;
        if (isFinished) {
            enemy.finished = std::make_tuple(true, ++finishedRacers);
        }
    }

    if(finishedRacers == enemies.size() + 1) {

    }
}

void Model::updateRacer() {

    auto element = _map->getCollisionElement(_racer._position.first,
                                             _racer._positionExtra.second,
                                             _racer._positionExtra.first,
                                             _racer._position.second);

    if (element != nullptr) {
        element->collision(_racer, _racerController, _currentCommand);
    }

    _racerController.changeRotationSpeed(_currentCommand, _racer);
    _racerController.changeSpeed(_racer, false);

    _racerController.updateRotation(_racer);
    _racerController.updatePosition(_racer);

    Response response{ViewEvent::RACER, std::make_optional(_racer), std::nullopt, std::nullopt};
    notifyObserves(response);
}

void Model::updateEnemies() {}