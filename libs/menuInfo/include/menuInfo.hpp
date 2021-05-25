#pragma once

#include <map>
#include <stdint.h>

struct RacerInfo {
    RacerInfo() = default;
    std::map<uint8_t, uint8_t> results;
};
