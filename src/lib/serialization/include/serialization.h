//
// Created by dark0ghost on 12.05.2021.
//
#pragma once
#ifndef LIBSERVER_SERIALIZATION_H
#define LIBSERVER_SERIALIZATION_H

#include <Position.hpp>

std::string writeToJson(const Position& pos) {
    return "{\"username\":" "\"" + pos.username + '"' + ",\"x\":" + pos.x + ",\"y\":" + pos.y + ",\"z\":" + pos.z + "}";
}
#endif //LIBSERVER_SERIALIZATION_H
