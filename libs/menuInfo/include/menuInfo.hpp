#pragma once

#include <vector>

struct RacerInfo {
    int ip; // sorry i don't know :)
    // something else
    int res = 0; // чтобы вконце например вернуть время ?..
};

struct MenuInfo {
    explicit MenuInfo(std::vector<RacerInfo>& _racersInfo): racersInfo(_racersInfo){};
    std::vector<RacerInfo> racersInfo;
};
