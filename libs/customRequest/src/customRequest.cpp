//
// Created by dark0ghost on 24.05.2021.
//
#include <customRequest.h>
cpr::Response CustomRequest::getRequest(const cpr::Url& url) {
    auto resp = cpr::Get(url);
    return resp;
}
