#include <memory>

#include "Map.h"

Map::Map(const std::string &filename) { stages = parser.parseFile(filename); }

std::vector<std::shared_ptr<AbstractElement>> Map::getDynamicElements() {
    for (auto &it : elements) {
        if (it->isElementDynamic()) {
            dynamicElements.push_back(it);
        }
    }
    return dynamicElements;
}

AbstractElement &Map::getCollisionElement(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    for (auto &it : elements) {
        bool isCollision = it->intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight);
        if (isCollision) {
            return *it;
        }
    }

    static Idle idle({0, 0}, {0, 0}, {0, 0});
    return idle;
}
std::vector<std::shared_ptr<AbstractElement>> Map::getStage() {
    for (const auto &stage : stages) {
        for (const auto &block : stage->blocks) {
            for (const auto &element : block->elements) {
                elements.push_back(element);
            }
        }
    }
    return elements;
}
