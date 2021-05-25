//
// Created by dark0ghost on 05.04.2021.
//
#pragma once
#ifndef LIBSERVER_ABSTRACTCLIENT_H
#define LIBSERVER_ABSTRACTCLIENT_H
#include <cstring>
#include <string>
#include <utility>
#include <curl_intarface.h>
#include <ConnectionData.hpp>
#include <deserialization.h>
#include <Position.hpp>

using namespace  cpr;

template<typename Request>
class GameClient{
    ConnectionData dataConnection;


public:
    explicit GameClient(ConnectionData connection1){
        dataConnection = std::move(connection1);
    }
    explicit GameClient(){
        dataConnection = ConnectionData();
    }



    template<typename Deserialization>
    Position getUpdates() {
     #ifndef test_jet_racing
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto response = Request::getRequest(Url(dataConnection.host + ":" + std::string(dataConnection.port) + "/get_updates"));
        Position res =  deserObject.getPositionFromJson(response.text);
        return res;
     #else
        return Position{"200"};
     #endif
    }


    void sendData(Position &userPosition) {
         Request::getRequest(Url(dataConnection.host + ":" + std::string(dataConnection.port) + "/set_position?username=" + userPosition.username + "&x=" + userPosition.x + "&y=" + userPosition.y + "&z=" + userPosition.z ));
    }

    int join(char*& username) {
        auto response = Request::getRequest(Url(dataConnection.host + ":" + reinterpret_cast<const char *>(dataConnection.port) + "/add?username=" + username));
        return response.status_code;
    }

    static inline std::vector<std::string> searchOpenSession(std::vector<std::string>& ipList, std::string port){
        auto result = std::vector<std::string>();
        for(const auto& i : ipList){
            auto response = Request::getRequest(Url(i + ":" + port + "/ping"));
            if(response){}
        }
        return std::vector<std::string>();
    }

};
#endif //LIBSERVER_ABSTRACTCLIENT_H
