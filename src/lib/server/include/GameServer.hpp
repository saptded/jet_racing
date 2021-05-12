//
// Created by dark0ghost on 05.04.2021.
//


#ifndef LIBSERVER_GAMESERVER_HPP
#define LIBSERVER_GAMESERVER_HPP

#include <Connection.hpp>
#include <Position.hpp>
#include <iostream>
#include <vector>


class [[maybe_unused]] GameServer{

    std::vector<Position> userBuffer;

public:

    auto ping(auto req){
        return req->create_response()
                .set_body("{'status': 200}")
                .done();
    }


    [[maybe_unused]] auto addUser(auto req, auto params) {
        const auto qp = parse_query(req->header().query());
        std::string username = std::string(qp["username"]);
        userBuffer.push_back(Position{username,"0","0", "0"});
        return req->create_response().set_body("{'status': 'ok'}}").done();
    }

    [[maybe_unused]] auto setNewPosition(auto req, auto params){
        const auto qp = parse_query(req->header().query());
        std::string username = std::string(qp["username"]);
        std::string x = std::string(qp["x"]);
        std::string y = std::string(qp["x"]);
        std::string z = std::string(qp["z"]);
        for (auto& i: userBuffer) {
            if(i.username == username){
                i = (Position{username, x,y, z});
                return req->create_response().set_body("{'status': 'ok'}}").done();
            }
        }
       /* bool res = false;
        std::copy_if(userBuffer.back(), userBuffer.end(),  std::insert_iterator (Position{username, x,y, z}), [username, &res](auto name){ res = (name.username ==  username);  return  name.username ==  username; });
        if(res){
            return req->create_response().set_body("{'status': 'ok'}}").done();
        }
        return req->create_response().set_body("{'status': 'fail'}}").done();*/
    }


    [[maybe_unused]] auto& sendNewPosition(auto& req, auto& params) {
        std::string response = "{";
        for (auto j = 0; j < userBuffer.size(); j++) {
            const auto &i = userBuffer[j];
            if (j != userBuffer.size())
                response += "'" + i.username + "': { 'x': {" + i.x + "}" + "," + "'y': {" + i.y + "}" + "," +
                            "'z': {" + i.z + "}" + "" + "},";
            response += "'" + i.username + "': { 'x': {" + i.x + "}" + "," + "'y': {" + i.y + "}" + "," +
                        "'z': {" + i.z + "}" + "" + "}";
        }
        response += '}';
        return req->create_response().set_body(response).done();
    }

    [[maybe_unused]] void close();
};

#endif //LIBSERVER_GAMESERVER_HPP
