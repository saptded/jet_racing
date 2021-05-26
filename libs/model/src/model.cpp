#include <cmath>
#include <functional>

#include "AbstractElement.h"
#include "model.hpp"

Model::Model(int id)
    : _map(std::make_unique<Map>(std::string("../maps/mapTest.xml")))
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

    auto element = _map->getCollisionElement(_racer._position.first, _racer._positionExtra.second, _racer._positionExtra.first, _racer._position.second);

    if (element != nullptr) {
        element->collision(_racer, _racerController, _currentCommand);
    }

    _racerController.changeRotationSpeed(_currentCommand, _racer);
    _racerController.changeSpeed(_racer, false);

    _racerController.updateRotation(_racer);
    _racerController.updatePosition(_racer);

    Response response{ViewEvent::RACER, std::make_optional(_racer), std::nullopt, std::nullopt};
    notifyObserves(response);
    Position pos = {menuInfo->myName, std::to_string(_racer._center.x), std::to_string(_racer._center.x), std::to_string(_racer._rotation) };
    _client->sendData(pos);
}

void Model::updateEnemies() {
    auto webInfo = _client->getUpdates();
    auto enemy = enemies.begin();
    for(auto &webEnemy: webInfo){
        if(webEnemy.first != menuInfo->myName){
            enemy->_center = { webEnemy.second.at(0) , webEnemy.second.at(1)};
            enemy->_rotation = webEnemy.second.at(2);
        }
    }
    Response response{ViewEvent::ENEMIES, std::nullopt, std::make_optional(enemies), std::nullopt};
    notifyObserves(response);
}

Model::Model(std::shared_ptr<MenuInfo> menuInfo):
_map(std::make_unique<Map>(std::string("../maps/testArc.xml")))
        , currentStage(0)
        , finishedRacers(0){
    _client = std::move(menuInfo->client);
    auto racers = _client->getUpdates();
    int id = 0;
    for(int i = 0; i < racers.size(); i++){
        if(racers.at(i).first == menuInfo->myName){
            id = i;
        }
    }
    _racer = Racer(_map->getStartPointByID(id), id);
    racers = _client->getUpdates();
    for(int i = 0; i < racers.size(); i++){
        if(racers.at(i).first != menuInfo->myName){
            Racer enemy(_map->getStartPointByID(i), i);
            enemies.push_back(enemy);
        }
    }
    Response response{ViewEvent::CHANGE_STAGE, std::nullopt, std::nullopt, std::make_optional(_map->getElementsInStage(currentStage))};
    notifyObserves(response);
}

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
