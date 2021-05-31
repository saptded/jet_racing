#include <cmath>
#include <functional>
#include <customDeserialization.h>
#include <deserialization.h>
#include "AbstractElement.h"
#include "model.hpp"
#include "GameClient.hpp"
#include "response.hpp"

Model::Model(int id)
    : _map(std::make_unique<Map>(std::string("../maps/stages.xml")))
    , _racer(_map->getStartPointByID(0), id)
    , currentStage(0)
    , finishedRacers(0){}

std::shared_ptr<MenuInfo> Model::updateModel(Command &rotation) {
    _currentCommand = rotation;

    updateMap();
    updateRacers();

    notifyObserves(std::make_shared<Response>());

    return menuInfo;
}

void Model::addObserver(Observer *observer) { _observes.push_back(observer); }

void Model::removeObserver(Observer *observer) { _observes.remove(observer); }

void Model::notifyObserves(std::shared_ptr<Response> response) {
    for (const auto &observer : _observes) {
        observer->handleEvent(response);
    }
}

Model::~Model() = default;

void Model::updateMap() {
    if(justStarted){
        notifyObserves(std::make_shared<Response>(_map->getElementsInStage(currentStage), currentStage, true));
        justStarted = false;
    }
    notifyObserves(std::make_shared<Response>(_map->getElementsInStage(currentStage), currentStage));
}

void Model::updateRacers() {
    updateRacer();
    updateEnemies();

    auto [isFinished, position] = _racer.finished;
    if (isFinished && position == 0) {
        _racer.finished = std::make_tuple(true, ++finishedRacers);
        Position pos = {std::to_string(myId), std::to_string(42), std::to_string(position)
                , std::to_string(_racer._rotation)
                , 42
                , position // поместили в stage место
                , true};
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

    notifyObserves(std::make_shared<Response>(_racer, currentStage));
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
            enemy->curStage = webEnemy.stage;
            if(webEnemy.isFinished){
                enemy->finished = std::make_tuple(true, webEnemy.stage);
            }
        }
    }
    notifyObserves(std::make_shared<Response>(enemies, currentStage));
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
}
