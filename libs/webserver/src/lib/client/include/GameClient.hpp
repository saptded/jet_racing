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
#include "customRequest.h"

//using namespace cpr;

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
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto response = Request::getRequest(cpr::Url(dataConnection.host + ":" + std::to_string(dataConnection.port) + "/get_updates"));
        auto res =  deserObject.getPositionFromJson(response.text);
        return res;
    }


    void sendData(Position &userPosition) {
        Request::getRequest(cpr::Url(dataConnection.host + ":" + std::to_string(dataConnection.port) + "/set_position?username=" + userPosition.username + "&x=" + userPosition.x + "&y=" + userPosition.y + "&rotation=" + userPosition.rotation + "&stage=" + std::to_string(userPosition.stage) + "&isFinished=" + std::to_string(userPosition.isFinished) + "&speed=" + std::to_string(userPosition.speed)));
    }

    template<typename Deserialization>
    size_t join(std::string& username) {
        //std::string str = dataConnection.host + ":" + reinterpret_cast<const char *>(dataConnection.port) + "/add?username=" + username;

        std::string str = dataConnection.host + ":" + std::to_string(dataConnection.port) + "/add?username=" + username;
        auto response = Request::getRequest(cpr::Url(str));
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto res = deserObject.getIdFromJson(response.text);
        return res;
    }

    void sendFlag(bool gameFlagStart){
        std::string str = dataConnection.host + ":" + std::to_string(dataConnection.port) + "/set_flag?flag=" + std::to_string(gameFlagStart);
        Request::getRequest(cpr::Url(str));
    }

    template<typename Deserialization>
    bool getFlag(){
        std::string str = dataConnection.host + ":" + std::to_string(dataConnection.port) + "/get_flag";
        auto response = Request::getRequest(cpr::Url(str));
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto res = deserObject.getFlagFromJson(response.text);
        return res;
    }

    static inline std::vector<std::string> searchOpenSession(std::vector<std::string>& ipList, std::string& port){
        auto result = std::vector<std::string>();
        for(const auto& i : ipList){
            auto response = Request::getRequest(cpr::Url(i + ":" + port + "/ping"));
            if(response){}
        }
        return std::vector<std::string>();
    }

};
#endif //LIBSERVER_ABSTRACTCLIENT_H