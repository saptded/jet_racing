//
// Created by dark0ghost on 14.04.2021.
//


#include <GameServer.hpp>


[[maybe_unused]] void GameServer::close() {
}

[[maybe_unused]] auto GameServer::addUser(auto req, auto params) {
    const auto qp = parse_query(req->header().query());

}

[[maybe_unused]] auto GameServer::setNewPosition(auto req, auto params) {
    return nullptr;
}

[[maybe_unused]] auto GameServer::sendNewPosition(auto req, auto params) {
    return nullptr;
}




