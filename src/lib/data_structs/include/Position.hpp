//
// Created by dark0ghost on 15.04.2021.
//
#pragma once
#ifndef LIBSERVER_POSITION_HPP
#define LIBSERVER_POSITION_HPP
#include <string>
struct Position{
    std::string username{};
    std::string x{};
    std::string y{};
    std::string rotation{};
    float speed{};
    int stage{};
    bool isFinished = false;
};
#endif //LIBSERVER_POSITION_HPP
