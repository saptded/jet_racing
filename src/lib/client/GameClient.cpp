//
// Created by dark0ghost on 15.04.2021.
//

#include <DataGame.hpp>
#include <vector>
#include <GameClient.hpp>



DataGame GameClient::getUpdates() {
    return DataGame(200,std::vector<UserPosition>());
}

void GameClient::close() {

}

void GameClient::sendData(DataGame &data) {
    data.status = 200;

}

std::string GameClient::getRequest() {
    return std::string();
}

std::string GameClient::getData() {
    return std::string();
}
