#include <memory>

#include "Map.h"

Map::Map(const std::string &filename) { stages = parser.parseFile(filename); }

std::shared_ptr<AbstractElement> Map::getCollisionElement(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight) {
    for (auto &element : elements) {
        bool isCollision = element->intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight);
        if (isCollision) {
            return element;
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<AbstractElement>> Map::getElementsInStage(int currentStage) { return stages[currentStage]->elements; }
