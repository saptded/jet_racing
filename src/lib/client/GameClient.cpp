//
// Created by dark0ghost on 15.04.2021.
//

#include <DataGame.hpp>
#include <vector>
#include <GameClient.hpp>
#include <Connection.hpp>
#include <curl_intarface.h>


/*
 * GameServer.sendNewPosition : /get_updates
 */
template<typename... Ts>
std::string  GameClient<Ts...>::getUpdates() {
    auto response = getRequest(Url(connection.host + ":" + std::string(connection.port) + "/get_updates"));
    return response.text;
}

template<typename... Ts>
void GameClient<Ts...>::sendData(UserPosition &userPosition) {
    std::string information = "{ 'username':'" + userPosition.first +"','x':" + userPosition.second.x + "," + "'y':" + userPosition.second.y + "," + "'z':" + userPosition.second.z + "}";
    auto response = getRequest(Url(connection.host + ":" + std::string(connection.port) + "/set_position"));

}

template<typename... Ts>
std::vector<std::string> GameClient<Ts...>::searchOpenSession(std::vector<std::string> ipList, std::string port) {
    auto result = std::vector<std::string>();
    for(const auto& i : ipList){
        auto response = getRequest(Url(i + ":" + port + "/ping"));
    }
    return std::vector<std::string>();
}


