#include <cmath>
#include <functional>

#include "AbstractElement.h"
#include "model.hpp"

Model::Model(int id)
    : _map(std::make_unique<Map>(std::string("../maps/testArc.xml"))), _racer(_map->getStartPointByID(0).first, id) {}

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

    Response response{ViewEvent::STAGE, std::nullopt, std::nullopt, std::make_optional(_map->getElementsInStage(0))};
    notifyObserves(response);
}

void Model::updateRacers() {
    updateRacer();
    updateEnemies();
}

void Model::updateRacer() {

    auto element = _map->getCollisionElement(_racer._position.first,
                                             _racer._positionExtra.second,
                                             _racer._positionExtra.first,
                                             _racer._position.second);

    if (element != nullptr) {
        element->collision(_racer, _racerController);
    }

    _racerController.changeRotationSpeed(_currentCommand, _racer);
    _racerController.changeSpeed(_racer, false);

    _racerController.updateRotation(_racer);
    _racerController.updatePosition(_racer);

    Response response{ViewEvent::RACER, std::make_optional(_racer), std::nullopt, std::nullopt};
    notifyObserves(response);
}

void Model::updateEnemies() {}

// double Model::lineCoefficient(const AbstractElement &line) {
//     double k = 0;
//     if (line.end.x == line.start.x) {
//         k = 10000000;
//     } else if (line.end.y == line.start.y) {
//         k = 0.000001;
//     } else {
//         k = ((line.end.y - line.start.y) / (line.end.x - line.start.x));
//     }
//     return k;
// }

// void Model::onCollision(const AbstractElement &collisionElement) {
//     switch (collisionElement.type) {
//         case line:
//             double k = lineCoefficient(collisionElement);
//             double b = collisionElement.start.y - collisionElement.start.x * k;
//             double lineX = (_racer._center.y - b) / k;
//             double lineY = k * _racer._center.x + b;
//
//             std::function<bool(double, double)> compX;
//             std::function<bool(double, double)> compY;
//
//             if (lineY > _racer._center.y + _racer._speed.speedY) {
//                 compY = [](double x1, double x2) { return x1 < x2; };
//             } else {
//                 compY = [](double x1, double x2) { return x1 > x2; };
//             }
//
//             if (lineX > _racer._center.x + _racer._speed.speedX) {
//                 compX = [](double x1, double x2) { return x1 < x2; };
//             } else {
//                 compX = [](double x1, double x2) { return x1 > x2; };
//             }
//
//             if (compY(lineY, _racer._position.first.y) || compX(lineX, _racer._position.first.x)) {  // back collision
//                 _racerController.changeSpeed(_racer, 0.1 * _racer._speed.speedX / 10, 0.1 * _racer._speed.speedX / 10);
//                 _racerController.changeRotationSpeed(_currentCommand, _racer, 0.3);
//             }
//
//             if (compY(lineY, _racer._center.y) || compX(lineX, _racer._center.x)) {  // front collision
//                 double extraAccelerateX = 2.6 * std::cos(90 * 180 / M_PI - std::atan(k)) * _racer._speed.speedX;
//                 double extraAccelerateY = 2.6 * std::sin(90 * 180 / M_PI - std::atan(k)) * _racer._speed.speedY;
//                 _racerController.changeSpeed(_racer, extraAccelerateX, extraAccelerateY);
//             }
//
//             _racerController.changeSpeed(_racer);
//             break;
//     }
// }
