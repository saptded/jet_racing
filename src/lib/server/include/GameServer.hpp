//
// Created by dark0ghost on 05.04.2021.
//


#ifndef LIBSERVER_GAMESERVER_HPP
#define LIBSERVER_GAMESERVER_HPP

#include <Connection.hpp>
#include <interface_for_high_level_api.h>
#include <Position.hpp>

class GameServer{

    std::vector<std::pair<std::string,Position<int>>> userBuffer;

    Connection connection;
    void route(){

    }
public:
    [[maybe_unused]] auto addUser(auto req, auto params);

    [[maybe_unused]] auto setNewPosition(auto req, auto params);

    [[maybe_unused]] auto sendNewPosition(auto req, auto params);

    [[maybe_unused]] void close();
};

#endif //LIBSERVER_GAMESERVER_HPP
