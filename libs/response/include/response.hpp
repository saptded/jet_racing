//<<<<<<< HEAD
#pragma once

#include "racer.hpp"
#include "AbstractElement.h"
#include <optional>

//};

//enum Event {
//    updateRacer,
//};
//
//struct Response {
//    Event event;
//    const std::optional<Racer *> _racer;
enum ViewEvent {
    INIT, RACER, ENEMIES, STAGE, CHANGE_STAGE, RENDER, RESULTS,
};

struct Response {
    ViewEvent eventType{};
    std::optional<Racer> racer;
    std::optional<std::vector<Racer>> enemies;
    std::optional<std::vector<std::shared_ptr<AbstractElement>>> stage;
};

//template<ViewEvent event>
//struct Response {};
//
//struct ResponseInit {
//    using Response = ::Response<INIT>;
//    Racer& racer;
//    std::vector<Racer>& enemies; // 0 по порядку - наш
//    std::vector<AbstractElement>& stage; // первый stage - туннели, dynamic objects
//    // событие отдельное думаю точно нужно, тк по нему будут вызываться конструкторы объектов
//};
//
//struct ResponseRacer {
//    using Response = ::Response<RACER>;
//    Racer& racer;
//};
//
//struct ResponseEnemies {
//    using Response = ::Response<ENEMIES>;
//    std::vector<Racer>& enemies;
//};
//
//struct ResponseStage {
//    using Response = ::Response<STAGE>;
//    std::vector<AbstractElement>& stage; // все объекты карты // только dynamic objects (прилетает каждую итерацию)
//};
//
//struct ResponseChangeStage {
//    using Response = ::Response<CHANGE_STAGE>;
//    std::vector<AbstractElement>& stage; // очередной stage - туннели, dynamic objects (2 раза)
//    // + обновление цветов
//};
//
//struct ResponseRender {
//    using Response = ::Response<RENDER>;
//    //как-то нужно после полного цикла обновления картинки (события racer, dynamics, и (не обязательно (?)) enemies) вызвать перерисовку sfml окна
//};
//
//struct ResponseResults {
//    using Response = ::Response<RESULTS>;
//    std::vector<int[2]> results;
//};
