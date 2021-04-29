//
// Created by Kseny
//
#pragma once

#include "utils.hpp"

enum ViewEvent {
    INIT, RESULTS, RACER, ENEMIES, DYNAMIC_OBJECTS, CHANGE_STAGE, RENDER
};

template<ViewEvent event>
struct Response {};

struct ResponseResults {
    using Response = ::Response<RESULTS>;
    std::vector<int[2]> results;
};

struct ResponseRacer {
    using Response = ::Response<RACER>; // ждет игрока едущего смотрящего вверх по экрану (голубое - машина, красное - огонь)
    Point point;
    Speed speed;
    int id; // прошу чтобы у собственного игрока было всегда 0, у остальных постоянно закрепленнное значение
    // это может быть избыточно, но пусть будет пока
};

struct ResponseEnemies {
    using Response = ::Response<ENEMIES>;
    std::vector<ResponseRacer> enemies;
};

struct ResponseDynamicObjects {
    using Response = ::Response<DYNAMIC_OBJECTS>;
    std::vector<abstractElement> elements; // только dynamic objects (прилетает каждую итерацию)
};

struct ResponseChangeStage {
    using Response = ::Response<CHANGE_STAGE>;
    std::vector<abstractElement> stage; // очередной stage - туннели, dynamic objects (2 раза)
};

struct ResponseInit {
    using Response = ::Response<INIT>;
    float height;
    float width;
    std::vector<ResponseRacer> racers; // 0 по порядку - наш
    std::vector<abstractElement> stage; // первый stage - туннели, dynamic objects
    // событие отдельное думаю точно нужно, тк по нему будут вызываться конструкторы объектов
};

struct ResponseRender {
    using Response = ::Response<RENDER>;
    //как-то нужно после полного цикла обновления картинки (события racer, dynamics, и (не обязательно (?)) enemies) вызвать перерисовку sfml окна
};
