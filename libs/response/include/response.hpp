//
// Created by Kseny
//
#pragma once

#include "utils.hpp"
#include "racer.hpp"

enum ViewEvent {
    INIT, RACER, ENEMIES, DYNAMIC_OBJECTS, CHANGE_STAGE, RENDER, RESULTS,
};

template<ViewEvent event>
struct Response {};

struct ResponseInit {
    using Response = ::Response<INIT>;
    std::vector<Racer>& racers; // 0 по порядку - наш
    std::vector<abstractElement>& stage; // первый stage - туннели, dynamic objects
    // событие отдельное думаю точно нужно, тк по нему будут вызываться конструкторы объектов
};

struct ResponseRacer {
    using Response = ::Response<RACER>;
    Racer& racer;
};

struct ResponseEnemies {
    using Response = ::Response<ENEMIES>;
    std::vector<Racer>& enemies;
};

struct ResponseDynamicObjects {
    using Response = ::Response<DYNAMIC_OBJECTS>;
    std::vector<abstractElement>& elements; // только dynamic objects (прилетает каждую итерацию)
};

struct ResponseChangeStage {
    using Response = ::Response<CHANGE_STAGE>;
    std::vector<abstractElement>& stage; // очередной stage - туннели, dynamic objects (2 раза)
};

struct ResponseRender {
    using Response = ::Response<RENDER>;
    //как-то нужно после полного цикла обновления картинки (события racer, dynamics, и (не обязательно (?)) enemies) вызвать перерисовку sfml окна
};

struct ResponseResults {
    using Response = ::Response<RESULTS>;
    std::vector<int[2]> results;
};
