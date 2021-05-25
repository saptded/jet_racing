//
// Created by dark0ghost on 25.05.2021.
//
#include <customDeserialization.h>
#include <customRequest.h>
#include <startServer.h>
#include <iostream>
#include <GameServer.hpp>
#include <GameClient.hpp>
int main(){
    bool isServer;
    std::cin >> isServer;
    if(isServer){
        GameServer gameServer = GameServer();
        ConnectionData connectionData = {2021, "localhost"}; // сетевые данные на которых запуститься сервер
        auto server = startServer(gameServer, connectionData);
    }

    ConnectionData data = ConnectionData{2021, "localhost"};
    auto gameClient = GameClient<CustomRequest>(data);
    std::string name = "isServer_" + std::to_string(isServer);
    gameClient.join<CustomDeserialization>(name);

    int letsgo;
    std::cin >> letsgo; // ждем

    gameClient.getUpdates<CustomDeserialization>();
}

