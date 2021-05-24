#pragma once

#include <map>

struct RacerInfo {
    RacerInfo() = default;
    std::map<uint8_t, uint8_t> results;
};
