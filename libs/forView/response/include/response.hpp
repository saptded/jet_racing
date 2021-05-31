#pragma once

#include "AbstractElement.h"
#include "racer.hpp"

#include <optional>

enum ViewEvent {
    RACER,
    ENEMIES,
    STAGE,
    CHANGE_STAGE,
    RENDER,
    RESULTS,
};

struct Response {
    explicit Response(Racer _racer, uint8_t _stage): curStage(_stage), eventType(RACER), racer(std::make_optional(_racer)), enemies(std::nullopt), stage(std::nullopt) {};
    explicit Response(std::vector<Racer> _enemies, uint8_t _stage): curStage(_stage), eventType(ENEMIES), racer(), enemies(std::make_optional(_enemies)), stage(std::nullopt) {};
    explicit Response(std::vector<std::shared_ptr<AbstractElement>> _map, uint8_t _stage): curStage(_stage), eventType(STAGE), racer(std::nullopt), enemies(std::nullopt), stage(std::make_optional(_map)) {};
    explicit Response(std::vector<std::shared_ptr<AbstractElement>> _map, uint8_t _stage, bool change): curStage(_stage), eventType(CHANGE_STAGE), racer(std::nullopt), enemies(std::nullopt), stage(std::make_optional(_map)) {};
    Response(): eventType(RENDER), racer(std::nullopt), enemies(std::nullopt), stage(std::nullopt) {};
    uint16_t curStage;
    ViewEvent eventType{};
    std::optional<Racer> racer;
    std::optional<std::vector<Racer>> enemies;
    std::optional<std::vector<std::shared_ptr<AbstractElement>>> stage;
};