//
// Created by dark0ghost on 24.05.2021.
//
#pragma once
#ifndef JET_RACING_CUSTOMREQUEST_H
#define JET_RACING_CUSTOMREQUEST_H
#define LIBSERVER_CURL_INTARFACE_H // нейтрализация интерфейса
#include "cpr/cpr.h"

struct CustomRequest{
   static cpr::Response getRequest(cpr::Url url);
};
#endif  // JET_RACING_CUSTOMREQUEST_H
