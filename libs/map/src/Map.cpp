#include <memory>

#include "Map.h"

Map::Map(const std::string &filename) { stages = parser.parseFile(filename); }

std::shared_ptr<AbstractElement> Map::getCollisionElement(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    for (auto &it : elements) {
        bool isCollision = it->intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight);
        if (isCollision) {
            return it;
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<Stage>> Map::getStages() { return stages; }
