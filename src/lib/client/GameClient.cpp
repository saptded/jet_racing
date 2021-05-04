//
// Created by dark0ghost on 15.04.2021.
//

#include <DataGame.hpp>
#include <vector>
#include <GameClient.hpp>



DataGame GameClient::get_updates() {
    return DataGame(200,std::vector<Position<int>>());
}

void GameClient::close() {

}

void GameClient::send_data(DataGame &data) {
    data.status = 200;

}

std::string GameClient::get_request() {
    return std::string();
}

std::string GameClient::get_data() {
    return std::string();
}
