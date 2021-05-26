#pragma once

#include <map>
#include <cstdint>
#include <memory>
#include <string>

class GameClient;

struct MenuInfo {
//    MenuInfo(std::string& _myName, std::shared_ptr<GameClient> _client) :
//    myName(_myName), client(std::move(_client)){};
    MenuInfo(std::string& _myName) :
            myName(_myName)
            {};
    MenuInfo() = default;
    std::string myName;
//    std::shared_ptr<GameClient> client;
    std::map<uint8_t, uint8_t> results;
};
