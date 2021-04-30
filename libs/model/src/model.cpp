#include "model.hpp"

Model::Model()
    : _racer({50, 50}) {}

void Model::updateModel(Rotation &rotation) {
    _currentCommand = rotation;

    updateMap();
    updateRacers();
}

void Model::addObserver(Observer *observer) { _observes.push_back(observer); }

void Model::removeObserver(Observer *observer) { _observes.remove(observer); }

void Model::notifyObserves(Response &response) {
    for (const auto &observer : _observes) {
        observer->handleEvent(response);
    }
}

Model::~Model() = default;

void Model::updateMap() {}

void Model::updateRacers() {
    updateRacer();
    updateEnemies();
}

void Model::updateRacer() {
    _racerController.changeRotation(_currentCommand, _racer);
    _racerController.update(_racer);

    Response response{Event::updateRacer, std::make_optional(&_racer)};
    notifyObserves(response);
}

void Model::updateEnemies() {}
