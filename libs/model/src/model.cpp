//
// Created by saptded on 15.04.2021.
//

#include "model.hpp"

Model::Model() : racer(Racer()) {}

Model::~Model() = default;

void Model::updateModel(RotationDirection &&rotationDirection) {
    updateMap();
    updateRacers(rotationDirection);
}

void Model::updateMap() {
    std::cout << "Map was updated" << std::endl;
}

void Model::updateRacers(RotationDirection &rotationDirection) {
    updateEnemies();
    updateRacer(rotationDirection);
}

void Model::updateRacer(RotationDirection &rotationDirection) {
    racer.updateRacerRotation(rotationDirection);
}

void Model::updateEnemies() {
    std::cout << "Get information from server" << std::endl;
}

void Model::notifyObserves(ModelResponse &response) {
    for (const auto& obs : observes) {
        obs->handleEvent(response);
    }
}

void Model::addObserver(Observer *observer) {
    observes.push_back(observer);
}

void Model::removeObserver(Observer *observer) {
    observes.remove(observer);
}
void Model::setObserves(const std::vector<Observer*>& obs) {
    for (auto o : obs) {
        addObserver(o);
    }
}

