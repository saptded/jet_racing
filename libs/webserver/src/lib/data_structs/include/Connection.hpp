//
// Created by dark0ghost on 04.05.2021.
//
#pragma once
#ifndef LIBSERVER_CONNECTION_HPP
#define LIBSERVER_CONNECTION_HPP


#include <string>

/*
 * mb make save url api ?
 */
struct Connection {
    std::string port = "80";
    std::string host = "localhost";
};
#endif //LIBSERVER_CONNECTION_HPP
