//
// Created by dark0ghost on 15.04.2021.
//

#include <DataGame.hpp>
#include <vector>
#include <GameClient.hpp>
#include <Connection.hpp>
#include <curl_intarface.h>



template<typename... Ts>
DataGame GameClient<Ts...>::getUpdates() {
    return DataGame(200,std::vector<UserPosition>());
}

template<typename... Ts>
void GameClient<Ts...>::close() {

}

template<typename... Ts>
void GameClient<Ts...>::sendData(DataGame &data) {
    data.status = 200;
}

template<typename... Ts>
std::vector<std::string> GameClient<Ts...>::searchOpenSession(std::vector<std::string> ipList, std::string port) {
    auto result = std::vector<std::string>();
    for(const auto& i : ipList){
        auto response = getRequest(Url(i + ":" + port + "/ping"));
    }
    return std::vector<std::string>();
}


