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

    std::string gameFlagStart = "0";

    std::vector<std::pair<std::string,Position>> userBuffer;
    std::vector<std::pair<std::string,std::string>> userName;

    size_t localId = 0;

    std::string getLocalId(){
        return std::to_string(localId++);
    }

    std::string getNameWithId(const std::string& idNumber){
        for(const auto& user: userName){
            if (idNumber == user.first){
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
        gameFlagStart = (flag);
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
        userBuffer.push_back(std::pair(local_id,Position{username,"0","0", "0",0.00,0,false}));
        return req->create_response().set_body(R"({"id":)" + local_id + R"(})");
    }

    [[maybe_unused]] auto setNewPosition(auto req) {
       const auto qp = parse_query(req->header().query());
        std::string id = std::string(qp["username"]);
        std::string username = getNameWithId(id);
        if(username == "error"){
            return req->create_response().set_body(R"({"status": "fail: name error"})");
        }
        std::string x = std::string(qp["x"]);
        std::string y = std::string(qp["y"]);
        std::string rotation = std::string(qp["rotation"]);
        float speed  = std::stof(std::string(qp["speed"]));
        int stage = atoi((std::string(qp["stage"]).c_str()));
        bool isFinished = (std::string(qp["isFinished"]) == std::string("0"));
        auto set = std::pair(id,Position{username, x,y, rotation,speed,stage,isFinished});
        #ifdef DEBUG
        std::cout << "username " << username << "\n";
        #endif
        bool res = false;
        std::replace_if(userBuffer.begin(),userBuffer.end(),[&username,&res](std::pair<std::string,Position>& pos){
            #ifdef DEBUG
            std::cout << "replace if check " << pos.second.username << "\n";
            #endif
            auto response = pos.second.username == username;
            res |= response;
            #ifdef DEBUG
            std::cout << "res check " << res << "\n";
            #endif
            return response;
        },set);
        #ifdef DEBUG
        std::cout << "server res " << res << "\n";
        #endif
        if(res) {
            return req->create_response().set_body(R"({"status": "ok"})");
        }
        return req->create_response().set_body(R"({"status": "fail: not found"})");
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
                    R"({"username":")" + i.username + R"(","x":")" + i.x + R"(","y":")" + i.y + R"(","rotation":")" + i.rotation + R"(","speed":)" + std::to_string(i.speed) + R"(,"stage":)" + std::to_string(i.stage) +  R"(,"isFinished":)" + std::to_string(i.isFinished) + "},";
            }

            const auto &endPositionRender = userBuffer[sizeUserBuffer - 1].second;
            response += R"({"username":")" + endPositionRender.username + R"(","x":")" + endPositionRender.x +
                        R"(","y":")" + endPositionRender.y  + R"(","rotation":")" + endPositionRender.rotation + R"(","speed":)" + std::to_string(endPositionRender.speed) + R"(,"stage":)" + std::to_string(endPositionRender.stage) + R"(,"isFinished":)" + std::string(
                   std::to_string(endPositionRender.isFinished)) + "}]";
            return req->create_response().set_body(response);
        }
        return req->create_response().set_body(response + "]");
    }

    [[maybe_unused]] void close();
};

#endif //LIBSERVER_GAMESERVER_HPP
