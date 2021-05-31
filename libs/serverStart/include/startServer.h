//
// Created by dark0ghost on 24.05.2021.
//
#pragma once
#ifndef JET_RACING_STARTSERVER_H
#define JET_RACING_STARTSERVER_H
#include <restinio/all.hpp>

using namespace restinio;
#include "traits.h"
#include <ConnectionData.hpp>
#include <GameServer.hpp>
/*
 * запускает сервер в пуле
 * server.stop(); - останавливает сервер;
 * server.wait(); - ждет остановки сервера;
 * poolSize - количество потоков.
 */
std::unique_ptr<running_server_instance_t<http_server_t<ServerTraits>>> startServer(GameServer& server, ConnectionData& connectionData, std::size_t poolSize = 16 );
#endif  // JET_RACING_STARTSERVER_H
