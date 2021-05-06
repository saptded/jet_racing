//
// Created by dark0ghost on 14.04.2021.
//


#include <GameServer.hpp>


[[maybe_unused]] void GameServer::close() {
    userBuffer.clear();
}

auto GameServer::ping(auto req, auto params) {
    return req->create_response().set_body("{'status': 200}").done();
}





