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
#include <algorithm>

class [[maybe_unused]] GameServer{

    std::string gameFlagStart = "false";

    std::vector<std::pair<std::string,Position>> userBuffer;
    std::vector<std::pair<std::string,std::string>> userName;

    size_t localId = -1;

    std::string getLocalId(){
        return std::to_string(localId++);
    }

    std::string getNameWithId(const std::string& idNumber){
        for(const auto& user: userName){
            if (idNumber == user.second){
                return user.second;
            }
        }
        return "error";
    }


public:

    constexpr auto ping(auto req){
        return req->create_response()
                .set_body(R"({"name":"jet_racing"})");
    }

    auto setStartFlag(auto req){
        const auto qp = parse_query(req->header().query());
        std::string flag = std::string(qp["flag"]);
        return req->create_response().set_body(R"({"status": "ok"})");
    }

    auto sendStartFlag(auto req){
        return req->create_response().set_body(R"({"flag":)" + gameFlagStart + R"(})");
    }


    [[maybe_unused]] auto addUser(auto req) {
        const auto qp = parse_query(req->header().query());
        std::string username = std::string(qp["username"]);
        std::string local_id = getLocalId();
        userName.push_back(std::pair(local_id, username));
        userBuffer.push_back(std::pair(local_id,Position{username,"0","0", "0"}));
        return req->create_response().set_body(R"({"id":)" + local_id + R"(})");
    }

    [[maybe_unused]] auto setNewPosition(auto req) {
        const auto qp = parse_query(req->header().query());
        std::string id = std::string(qp["username"]);
        std::string username = getNameWithId(id);
        if(username == "error"){
            return req->create_response().set_body(R"({"status": "fail"})");
        }
        std::string x = std::string(qp["x"]);
        std::string y = std::string(qp["x"]);
        std::string z = std::string(qp["z"]);
        bool res = false;
        std::replace_if(userBuffer.begin(),userBuffer.end(),[username,&res](const std::pair<std::string,Position>& pos){
            auto response = pos.first == username;
            res |= response;
            return response;
        },std::pair(id,Position{username, x,y, z}));
        if(res){
            return req->create_response().set_body(R"({"status": "ok"})");
        }
        return req->create_response().set_body(R"({"status": "fail"})");
    }



    [[maybe_unused]] auto sendNewPosition(auto req) {
        std::string response = "[";
        /*
         * использование replace_if не дает  реализовать  алгоритм за O(n);
         */
        auto sizeUserBuffer = userBuffer.size();
        if(sizeUserBuffer != 0) {
            for (auto j = 0; j < sizeUserBuffer - 1; j++) {
                const auto &i = userBuffer[j].second;
                response +=
                    R"({"username":")" + i.username + R"(","x":")" + i.x + R"(","y":")" + i.y + R"(","z":")" + i.z +
                    "\"},";
            }
            const auto &endPositionRender = userBuffer[sizeUserBuffer - 1].second;
            response += R"({"username":")" + endPositionRender.username + R"(","x":")" + endPositionRender.x +
                        R"(","y":")" + endPositionRender.y + R"(","z":")" + endPositionRender.z + "\"}]";
            return req->create_response().set_body(response);
        }
        return req->create_response().set_body(response + "]");
    }

    [[maybe_unused]] void close();
};

#endif //LIBSERVER_GAMESERVER_HPP
