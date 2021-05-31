#pragma once

#include <map>
#include <cstdint>
#include <memory>
#include <string>

class CustomRequest;

template<typename Request>
class GameClient;

struct MenuInfo {
    MenuInfo(std::string &_myName, int _myId, std::shared_ptr<GameClient<CustomRequest>> _client) :
            myName(_myName), myId(_myId), client(std::move(_client)) {};
    MenuInfo() = default;
    std::string myName;
    uint8_t myId;
    std::shared_ptr<GameClient<CustomRequest>> client;
    //std::map<uint8_t, uint8_t> results;
};
