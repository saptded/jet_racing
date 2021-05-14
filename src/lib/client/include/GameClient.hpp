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
#include <deserialization.h>
#include <Position.hpp>

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



    template<typename Deserialization>
    Position getUpdates() {
     #ifndef test_jet_racing
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto response = Request::getRequest(Url(connection.host + ":" + std::string(connection.port) + "/get_updates"));
        Position res =  deserObject.getPositionFromJson(response.text);
        return res;
     #else
        return Position{"200"};
     #endif
    }


    void sendData(Position &userPosition) {
        auto response = Request::getRequest(Url(connection.host + ":" + std::string(
                reinterpret_cast<const char *>(connection.port)) + "/set_position?username=" + userPosition.username + "&x=" + userPosition.x + "&y=" + userPosition.y + "&z=" + userPosition.z ));
    }

    int join(const std::string& username) {
        auto response = Request::getRequest(Url(connection.host + ":" + std::string(connection.port) + "/add?username=" + username));
        return response.status_code;
    }

    static inline std::vector<std::string> searchOpenSession(std::vector<std::string> ipList, std::string port){
        auto result = std::vector<std::string>();
        for(const auto& i : ipList){
            auto response = Request::getRequest(Url(i + ":" + port + "/ping"));
        }
        return std::vector<std::string>();
    }

};
#endif //LIBSERVER_ABSTRACTCLIENT_H
