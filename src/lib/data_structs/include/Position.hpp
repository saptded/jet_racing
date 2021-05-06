//
// Created by dark0ghost on 15.04.2021.
//

#ifndef LIBSERVER_POSITION_HPP
#define LIBSERVER_POSITION_HPP
#include <string>
struct Position{
    std::string x{};
    std::string y{};
    std::string z{};
};

using UserPosition = std::pair<std::string, Position>;
#endif //LIBSERVER_POSITION_HPP
