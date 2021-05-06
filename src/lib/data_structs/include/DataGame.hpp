//
// Created by dark0ghost on 13.04.2021.
//

#ifndef LIBSERVER_DATAGAME_HPP
#define LIBSERVER_DATAGAME_HPP
#include "Position.hpp"
#include <utility>
#include <vector>
#include <string>

using UserPosition = std::pair<std::string, Position<int>>;

struct DataGame{
    DataGame(int i, std::vector<UserPosition> vector): position(std::move(vector)) {
        status = i;
    }


    DataGame()  = default;

    explicit DataGame(std::vector<UserPosition> vector): position(std::move(vector)) {

    }

    std::vector<UserPosition> position{};
    int status{};



};
#endif //LIBSERVER_DATAGAME_HPP
