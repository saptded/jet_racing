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
#include <customRequest.h>

//using namespace  cpr;

//template<typename Request>
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
        //DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        //auto response = Request::getRequest(Url(dataConnection.host + ":" + std::to_string(8080) + "/get_updates"));
        //auto res =  deserObject.getPositionFromJson(response.text);
        //return res;
    }

    std::vector<std::pair<std::string,std::vector<float>>> getUpdates() {
        std::string string = "localhost:" + std::to_string(8080) + "/get_updates";
        const auto url = cpr::Url(string);
        auto response = CustomRequest::getRequest(url);
        char * str = const_cast<char*>(response.text.c_str());

        std::vector<float>playerCoords;
        std::vector<std::pair<std::string,std::vector<float>>> returnCoords;
// "[{\"username\"customName:\"\",\"x\":\"0\",\"y\":\"0\",\"z\":\"0\"},{\"username\":\"\",\"x\":\"0\",\"y\":\"0\",\"z\":\"0\"}]"
        while(*str != '\0')
        {
            bool ended = false;
            while((*str < 97)||(*str > 122)) {
                str++; // пропускаем начало строки
                if(*str == '\0'){
                    ended = true;
                    break;
                }
            }
            if(ended) continue;
            while( *str >= 97 && *str <= 122 ) str++; // пропускаем "username"
            while((*str < 97)||(*str > 122)) str++; // пропускаем промежуточные символы
            std::string name;
            while( *str >= 97 && *str <= 122 ) { // считываем имя
                name.push_back(*str);
                str++;
            }
            for(int i = 0; i < 3; i++){ // три раза доходим до числа и считываем его. ограничены длиной числа в 10 char
                while( !(*str >= '0' && *str <= '9')){
                    ++str;
                }
                playerCoords.push_back((float)std::stoi(str));
                str++;
            }
            returnCoords.emplace_back(std::make_pair(name, playerCoords));
            playerCoords.clear();
        }
        return returnCoords;
    }


    void sendData(Position &userPosition) {
         CustomRequest::getRequest(cpr::Url(dataConnection.host + ":" + std::to_string(dataConnection.port) + "/set_position?username=" + userPosition.username + "&x=" + userPosition.x + "&y=" + userPosition.y + "&z=" + userPosition.z ));
    }

    template<typename Deserialization>
    std::string join(std::string& username) {
        //std::string str = dataConnection.host + ":" + reinterpret_cast<const char *>(dataConnection.port) + "/add?username=" + username;

        std::string str = dataConnection.host + ":" + std::to_string(8080) + "/add?username=" + username;
        auto response = CustomRequest::getRequest(cpr::Url(str));
        //DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        //auto res = deserObject.getIdFromJson(response.text);
        //return res;
        return "";
    }

    void sendFlag(bool gameFlagStart){
        std::string str = dataConnection.host + ":" + std::to_string(dataConnection.port) + "/add?flag=" + std::to_string(gameFlagStart);
    }

    static inline std::vector<std::string> searchOpenSession(std::vector<std::string>& ipList, std::string& port){
        auto result = std::vector<std::string>();
        for(const auto& i : ipList){
            auto response = CustomRequest::getRequest(cpr::Url(i + ":" + port + "/ping"));
        }
        return std::vector<std::string>();
    }

};
#endif //LIBSERVER_ABSTRACTCLIENT_H
