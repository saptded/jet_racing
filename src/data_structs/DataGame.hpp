//
// Created by dark0ghost on 13.04.2021.
//

#ifndef LIBSERVER_DATAGAME_HPP
#define LIBSERVER_DATAGAME_HPP
#include "Position.hpp"
#include <utility>
#include <vector>
struct DataGame{
    DataGame(int i, std::vector<Position> vector): position(std::move(vector)) {
         status = i;
    }


    DataGame()  = default;

    DataGame(std::vector<Position> vector): position(std::move(vector)) {

    }

    std::vector<Position> position{};
    int status{};



};
#endif //LIBSERVER_DATAGAME_HPP
