//
// Created by dark0ghost on 05.04.2021.
//


#ifndef LIBSERVER_GAMESERVER_HPP
#define LIBSERVER_GAMESERVER_HPP

#include <Connection.hpp>
#include <interface_for_high_level_api.h>


class GameServer{
    Connection connection;
    void route(){

    }
public:
    explicit GameServer(Connection connection1);
    void start(run);
    void close();
};

#endif //LIBSERVER_GAMESERVER_HPP
