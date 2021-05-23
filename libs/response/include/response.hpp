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
    ViewEvent eventType{};
    std::optional<Racer> racer;
    std::optional<std::vector<Racer>> enemies;
    std::optional<std::vector<std::shared_ptr<AbstractElement>>> stage;
};
