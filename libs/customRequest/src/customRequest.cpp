//
// Created by dark0ghost on 24.05.2021.
//
#include <customRequest.h>
#include "../include/customRequest.h"

cpr::Response CustomRequest::getRequest(cpr::Url url) {
    auto resp = cpr::Get(url);
    return resp;
}

