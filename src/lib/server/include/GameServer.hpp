//
// Created by dark0ghost on 05.04.2021.
//

#pragma once
#ifndef LIBSERVER_GAMESERVER_HPP
#define LIBSERVER_GAMESERVER_HPP

#include <ConnectionData.hpp>
#include <Position.hpp>
#include <iostream>
#include <vector>

class [[maybe_unused]] GameServer{

    std::vector<Position> userBuffer;

public:

    constexpr auto ping(auto req){
        return req->create_response()
                .set_body(R"({"name":"jet_racing"})");
    }


    [[maybe_unused]] auto addUser(auto req) {
        const auto qp = parse_query(req->header().query());
        std::string username = std::string(qp["username"]);
        userBuffer.push_back(Position{username,"0","0", "0"});
        return req->create_response().set_body(R"({"status": "ok"}})");
    }

    [[maybe_unused]] auto setNewPosition(auto req) {
        const auto qp = parse_query(req->header().query());
        std::cout << 1;
        std::string username = std::string(qp["username"]);
        std::string x = std::string(qp["x"]);
        std::string y = std::string(qp["x"]);
        std::string z = std::string(qp["z"]);
        bool res = false;
        std::replace_if(userBuffer.begin(),userBuffer.end(),[username,&res](const Position& pos){
            auto response = pos.username == username;
            res |= response;
            return response;
        },Position{username, x,y, z} );
        if(res){
            return req->create_response().set_body(R"({"status": "ok"}})").done();
        }
        return req->create_response().set_body(R"({"status": "fail"}})").done();
    }


    [[maybe_unused]] auto sendNewPosition(auto req) {
        std::string response = "[";
        /*
         * использование replace_if не дает  реализовать  алгоритм за O(n);
         */
        auto sizeUserBuffer = userBuffer.size();
        for (auto j = 0; j < sizeUserBuffer - 1; j++) {
            const auto &i = userBuffer[j];
            response += R"({"username":")"+ i.username +R"(","x":")" + i.x + R"(","y":")" + i.y + R"(","z":")" + i.z + "\"},";
        }
        const auto& endPositionRender = userBuffer[sizeUserBuffer - 1];
        response += R"({"username":")"+ endPositionRender.username +R"(","x":")" + endPositionRender.x + R"(","y":")" + endPositionRender.y + R"(","z":")" + endPositionRender.z + "\"}]";
        return req->create_response().set_body(response).done();
    }

    [[maybe_unused]] void close();
};

#endif //LIBSERVER_GAMESERVER_HPP
