//
// Created by dark0ghost on 13.04.2021.
//

#ifndef LIBSERVER_DATAGAME_HPP
#define LIBSERVER_DATAGAME_HPP
#include "Position.hpp"
#include <vector>
struct DataGame{
    std::vector<Position> position{};
    int status;



};
#endif //LIBSERVER_DATAGAME_HPP
