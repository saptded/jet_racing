#include "model.hpp"

//enum Type {
//    line,
//};
//
//typedef struct AbstractElement {
//    virtual void updateElement() = 0;
//
//    Type type{};
//    Point start{};
//    Point end{};
//    Point center{};
//    bool isDynamic{};
//} AbstractElement;
//
//typedef struct Line : public AbstractElement {
//    Line(Type type, Point, Point, Point, bool b) {}
//    void updateElement() override{};
//} Line;
//
//[[maybe_unused]] Line lineElem = {Type::line, {0, 50}, {1280, 50}, {640, 50}, false};

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
    _racerController.changeRotationSpeed(_currentCommand, _racer);
    _racerController.changeSpeed(_racer);

    _racerController.updateRotation(_racer);
    _racerController.updatePosition(_racer);

    Response response{Event::updateRacer, std::make_optional(&_racer)};
    notifyObserves(response);
}

void Model::updateEnemies() {}

//void Model::onCollision(const AbstractElement &element) {
//    switch (element.type) {
//        case line:
//
//            break;
//    }
//}
