#pragma once

#include "racer.hpp"
#include <optional>

enum Event {
    updateRacer,
};

struct Response {
    Event event;
    const std::optional<Racer *> _racer;
};
