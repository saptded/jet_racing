//
// Created by dark0ghost on 25.05.2021.
//

#ifndef JET_RACING_CUSTOMDESERIALIZATION_H
#define JET_RACING_CUSTOMDESERIALIZATION_H
#include <Position.hpp>
#include <string>
#include <vector>
class [[maybe_unused]] CustomDeserialization{

    std::vector<Position> jsonToPosition(const char *json);

};
#endif  // JET_RACING_CUSTOMDESERIALIZATION_H
