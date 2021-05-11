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


template<typename Request>
std::vector<std::string> GameClient<Request>::searchOpenSession(std::vector<std::string> ipList, std::string port) {
    auto result = std::vector<std::string>();
    for(const auto& i : ipList){
        auto response = Request::getRequest(Url(i + ":" + port + "/ping"));
    }
    return std::vector<std::string>();
}

template<typename Request>
void GameClient<Request>::join(std::string username) {
    auto response = Request::getRequest(Url(connection.host + ":" + std::string(connection.port) + "/add?username=" + username));
}




