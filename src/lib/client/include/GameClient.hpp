//
// Created by dark0ghost on 05.04.2021.
//

#ifndef LIBSERVER_ABSTRACTCLIENT_H
#define LIBSERVER_ABSTRACTCLIENT_H
#include "DataGame.hpp"
#include <cstring>
#include <string>
#include <utility>
#include <curl_intarface.h>
#include <Connection.hpp>

template<typename Request>
class GameClient{
     Connection connection;
     //Response (&getRequest)(Ts&&... ts);

public:
    explicit GameClient(Connection connection1){// Response (get)(Ts&&...)){
        connection = std::move(connection1);
       // getRequest = get;
    }
    explicit GameClient(){
        connection = Connection();
    }

    std::string getUpdates() {
     #ifndef test_jet_racing
        auto response = Request::getRequest(Url(connection.host + ":" + std::string(connection.port) + "/get_updates"));
        return response.text;
     #else
        return "200";
     #endif
    }


    void sendData(UserPosition &userPosition) {
        auto response = Request::getRequest(Url(connection.host + ":" + std::string(
                reinterpret_cast<const char *>(connection.port)) + "/set_position?username=" + userPosition.first + "&x=" + userPosition.second.x + "&y=" + userPosition.second.y + "&z=" + userPosition.second.z ));
    }

    void join(std::string username);

    std::vector<std::string> searchOpenSession(std::vector<std::string> ipList, std::string port);
};
#endif //LIBSERVER_ABSTRACTCLIENT_H
