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


template<typename Request, typename UrlBuilder>
class GameClient{
    UrlBuilder urlBuilder;


public:
    template<typename Deserialization>
    std::vector<Position> getUpdates() {
#ifndef test_jet_racing
        DeserializationObject<Deserialization> deserObject =
        DeserializationObject<Deserialization>();
        auto url = urlBuilder.createGetUpdateUrl(dataConnection.host, dataConnection.port) + "/get_updates");
        auto response = Request::getRequest(Url(url));
        auto res = deserObject.getPositionFromJson(response.text);
        return res;
#else
        auto pos = Position{"200"};
        auto res = std::vector<Position>();
        res.push_back(pos);
        return res;
#endif
    }


    void sendData(Position &userPosition) {
        auto res = Request::getRequest(Url(urlBuilder.createSendDataUrl(userPosition.username, userPosition.x, userPosition.y, userPosition.rotation, userPosition.stage, userPosition.isFinished, userPosition.speed)));
#ifdef DEBUG
        std::cout << res.text << " response\n";
#endif
    }

    template<typename Deserialization>
    size_t join(std::string& username) {
        auto response = Request::getRequest(Url(urlBuilder.createJoinUrl(username)));
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto res = deserObject.getIdFromJson(response.text);
        return res;
    }

    void sendFlag(bool gameFlagStart){
        Request::getRequest(Url(urlBuilder.createSendFlagUrl(gameFlagStart)));
    }

    template<typename Deserialization>
    bool getFlag(){
        auto response = Request::getRequest(Url(urlBuilder.createGetFlagUrl()));
        DeserializationObject<Deserialization> deserObject =  DeserializationObject<Deserialization>();
        auto res = deserObject.getFlagFromJson(response.text);
        return res;
    }
};
#endif //LIBSERVER_ABSTRACTCLIENT_H
