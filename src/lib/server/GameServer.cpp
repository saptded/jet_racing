//
// Created by dark0ghost on 14.04.2021.
//


#include <GameServer.hpp>
#include <algorithm>
#include <Connection.hpp>
#include <iostream>


GameServer::GameServer(Connection connection1) : connection(std::move(connection1)) {
        route();
    }
void GameServer::start(run runs) {
    // runs();
}

void GameServer::close() {
    std::cout << 1;
}




