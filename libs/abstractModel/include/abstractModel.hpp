#pragma once

#include <map>

#include "mechanicalValues.hpp"
#include "observer.hpp"

// не моя часть
struct MenuInfo {
    //    MenuInfo(std::string& _myName, std::shared_ptr<GameClient> _client) :
    //    myName(_myName), client(std::move(_client)){};
    explicit MenuInfo(std::string &_myName)
        : myName(_myName){};
    MenuInfo() = default;
    std::string myName;
    //    std::shared_ptr<GameClient> client;
    std::map<uint8_t, uint8_t> results;
};

class AbstractModel : public Observable {
public:
    virtual std::shared_ptr<MenuInfo> updateModel(Command &rotation) = 0;

private:
};
