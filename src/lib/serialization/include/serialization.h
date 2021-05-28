//
// Created by dark0ghost on 12.05.2021.
//
#pragma once
#ifndef LIBSERVER_SERIALIZATION_H
#define LIBSERVER_SERIALIZATION_H

#include <Position.hpp>

std::string writeToJson(const Position& pos) {
    return   R"({"username":")" + pos.username + R"(","x":")" + pos.x + R"(","y":")" +  pos.y + R"(","rotation":")" +  pos.rotation + R"(","speed":)" + std::to_string(pos.speed) + R"(,"stage":)" + std::to_string(pos.stage) +  R"(,"isFinished":)" + std::to_string(pos.isFinished) + "}";
}
#endif //LIBSERVER_SERIALIZATION_H
