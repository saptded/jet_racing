//
// Created by dark0ghost on 05.04.2021.
//

#ifndef LIBSERVER_ABSTRACTCLIENT_H
#define LIBSERVER_ABSTRACTCLIENT_H
#include <cstring>
#include <string>
#include <utility>
#include <curl_intarface.h>
#include <Connection.hpp>
#include <Position.hpp>
#include <vector>


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
        auto response = Request::getRequest(Url(connection.host + ":" +  connection.port + "/get_updates"));
        return response.text;
    }


    void sendData(Position &userPosition) {
        auto response = Request::getRequest(Url(connection.host + ":" +
               connection.port + "/set_position?username=" + userPosition.username + "&x=" + userPosition.x + "&y=" + userPosition.y + "&z=" + userPosition.z ));
    }

    void join(std::string username);

    std::vector<std::string> searchOpenSession(std::vector<std::string> ipList, std::string port);
};
#endif //LIBSERVER_ABSTRACTCLIENT_H
