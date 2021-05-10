#include <iostream>
#include <memory>

#include "Map.h"

Map::Map(const std::string &filename) {
    stages = parser.parseFile(filename);
}

std::vector<std::shared_ptr<AbstractElement>> Map::getDynamicElements(size_t pos_x, size_t pos_y) {
    for (auto &it : elements) {
        if (it->isElementDynamic()) {
            dynamicElements.push_back(it);
        }
    }
    return dynamicElements;
}

AbstractElement &Map::getCollisionElement(Point posStart, Point posEnd, Point posCenter) {
    for (auto &it : elements) {
        bool isCollision = it->intersect(posStart, posCenter);
        if (isCollision) {
            return *it;
        }
    }

    static Idle idle({0, 0}, {0, 0}, {0, 0});
    return idle;
}

//Stage &Map::getCurrentStage(Point posStart, Point posEnd, Point posCenter) {
//    std::cout << "Using car's position calculate in what stage he is" << std::endl;
//    return stage;
//}
