//
// Created by dark0ghost on 05.04.2021.
//


#ifndef LIBSERVER_GAMESERVER_HPP
#define LIBSERVER_GAMESERVER_HPP

#include <Connection.hpp>

class run_on_this_thread_settings_t;


typedef void(run)(run_on_this_thread_settings_t &&settings);


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
