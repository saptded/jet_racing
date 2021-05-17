#include <cmath>
#include <functional>

#include "AbstractElement.h"
#include "model.hpp"

enum Type {
    line,
};

// typedef struct AbstractElement {
//     AbstractElement(Type type, Point start, Point end, Point center, bool isDynamic)
//         : type(type)
//         , start(start)
//         , end(end)
//         , center(end)
//         , isDynamic(isDynamic) {}
//
//     Type type;
//     Point start;
//     Point end;
//     Point center;
//     bool isDynamic;
//
//     virtual void updateElement(){};
// } AbstractElement;
//
// typedef struct Line : public AbstractElement {
//     Line(Type type, Point start, Point end, Point center, bool isDynamic)
//         : AbstractElement(type, start, end, center, isDynamic) {}
//     void updateElement() override{};
// } Line;

//[[maybe_unused]] Line lineElem = {Type::line, {0, 50}, {1280, 50}, {640, 50}, false};

Model::Model()
    : _racer({450, 350}), map(std::make_unique<Map>(std::string("/home/kseny/tp/JET/maps/mapTest.xml"))) {
}

void Model::updateModel(Rotation &rotation) {
    _currentCommand = rotation;

    updateRacers();
    updateMap();

    //там window.display()
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
    Response response{ViewEvent::STAGE, std::nullopt, std::nullopt, std::make_optional(map->getElementsInStage(0))};

    notifyObserves(response);
}

void Model::updateRacers() {
    updateRacer();
    updateEnemies();
}

void Model::updateRacer() {

        //onCollision(obj1);
        _racerController.changeRotationSpeed(_currentCommand, _racer);

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
