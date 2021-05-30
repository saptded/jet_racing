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
    std::vector<Position> getUpdates() {
     #ifndef test_jet_racing
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto response = Request::getRequest(Url(dataConnection.host + ":" + std::string(dataConnection.port) + "/get_updates"));
        auto res =  deserObject.getPositionFromJson(response.text);
        return res;
     #else
        auto pos = Position{"200"};
        auto res = std::vector<Position>();
        res.push_back(pos);
        return res;
     #endif
    }


    void sendData(Position &userPosition) {
        auto res = Request::getRequest(Url(dataConnection.host + ":" + std::to_string(dataConnection.port) + "/set_position?username=" + userPosition.username + "&x=" + userPosition.x + "&y=" + userPosition.y + "&rotation=" + userPosition.rotation + "&stage=" + std::to_string(userPosition.stage) + "&isFinished=" + std::to_string(userPosition.isFinished) + "&speed=" + std::to_string(userPosition.speed)));
        #ifdef DEBUG
         std::cout << res.text << " response\n";
        #endif
    }

    template<typename Deserialization>
    size_t join(std::string& username) {
        std::string str = dataConnection.host + ":" + std::to_string(dataConnection.port) + "/add?username=" + username;
        auto response = Request::getRequest(Url(str));
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto res = deserObject.getIdFromJson(response.text);
        return res;
    }

    void sendFlag(bool gameFlagStart){
        std::string str = dataConnection.host + ":" + std::to_string(dataConnection.port) + "/set_flag?flag=" + std::to_string(gameFlagStart);
        Request::getRequest(Url(str));
    }

    template<typename Deserialization>
    bool getFlag(){
        std::string str = dataConnection.host + ":" + std::to_string(dataConnection.port) + "/get_flag";
        auto response = Request::getRequest(Url(str));
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto res = deserObject.getFlagFromJson(response.text);
        return res;
    }
};
#endif //LIBSERVER_ABSTRACTCLIENT_H
