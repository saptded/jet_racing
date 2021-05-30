#include <cmath>
#include <functional>
#include <customDeserialization.h>
#include <deserialization.h>
#include <GameServer.hpp>
#include "AbstractElement.h"
#include "model.hpp"
#include "GameClient.hpp"

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
        Position pos = {std::to_string(myId), std::to_string(42), std::to_string(_racer._center.y)
                , std::to_string(_racer._rotation)
                , 42
                , position, true}; // поместили в stage место
        _client->sendData(pos);
        menuInfo = std::make_shared<MenuInfo>();
        menuInfo->myName = myName;
        menuInfo->client = std::move(_client);
    }

    for (auto &enemy : enemies) {
        auto [isFinished, position] = enemy.finished;
        if (isFinished && position == 0) {
            enemy.finished = std::make_tuple(true, ++finishedRacers);
        }
    }
//    if (finishedRacers == enemies.size() + 1) {
//        menuInfo = std::make_shared<MenuInfo>();
//        auto [isFinished, position] = _racer.finished;
//        menuInfo->results[_racer._id] = position;
//        for (auto &enemy : enemies) {
//            auto [isEnemyFinished, enemyPosition] = enemy.finished;
//            menuInfo->results.insert(std::make_pair(enemy._id, enemyPosition));
//        }
//
//        menuInfo->client = _client;
//    }
}

void Model::updateRacer() {

    auto element = _map->getCollisionElement(_racer._position.first, _racer._positionExtra.second, _racer._positionExtra.first, _racer._position.second, _racer._bottomCenter);

    if (element != nullptr) {
        element->collision(_racer, _racerController, _currentCommand);
    }

    _racerController.changeRotationSpeed(_currentCommand, _racer);
    _racerController.changeSpeed(_racer, false);

    _racerController.updateRotation(_racer);
    _racerController.updatePosition(_racer);

    Response response{ViewEvent::RACER, std::make_optional(_racer), std::nullopt, std::nullopt};
    notifyObserves(response);
    Position pos = {std::to_string(myId), std::to_string(_racer._center.x), std::to_string(_racer._center.y)
                    , std::to_string(_racer._rotation)
                    , sqrtf(powf(_racer._speed.speedX, 2)+powf(_racer._speed.speedY, 2))
                    , currentStage};
    _client->sendData(pos);
}

void Model::updateEnemies() {
    auto webInfo = _client->getUpdates<CustomDeserialization>();
    auto enemy = enemies.begin();
    for(auto &webEnemy: webInfo){
        if(webEnemy.username != myName){
            _racerController.updatePosition(*enemy, Point{ std::stof(webEnemy.x) , std::stof(webEnemy.y)});
            enemy->_rotation = std::stof(webEnemy.rotation);
            enemy->_speed.speedX = webEnemy.speed;
            if(webEnemy.isFinished){
                enemy->finished = std::make_tuple(true, webEnemy.stage);
            }
        }
    }
    Response response{ViewEvent::ENEMIES, std::nullopt, std::make_optional(enemies), std::nullopt};
    notifyObserves(response);
}

Model::Model(std::shared_ptr<MenuInfo> menuInfo):
_map(std::make_unique<Map>(std::string("../maps/testArc.xml")))
        , currentStage(0)
        , finishedRacers(0)
        ,_client(std::move(menuInfo->client))
        ,myName(menuInfo->myName)
        ,myId(menuInfo->myId){
    _racer = Racer(_map->getStartPointByID(menuInfo->myId), menuInfo->myId);
    Position pos = {myName, std::to_string(_racer._center.x), std::to_string(_racer._center.x), std::to_string(_racer._rotation) };
    _client->sendData(pos);
    auto racers = _client->getUpdates<CustomDeserialization>();
    for(int i = 0; i < racers.size(); i++){
        if(racers.at(i).username != myName){
            Racer enemy(_map->getStartPointByID(i), i);
            enemies.push_back(enemy);
        }
    }
    Response response{ViewEvent::CHANGE_STAGE, std::nullopt, std::nullopt, std::make_optional(_map->getElementsInStage(currentStage))};
    notifyObserves(response);
}
