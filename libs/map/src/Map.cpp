#include <memory>

#include "Map.h"

Map::Map(const std::string &filename) {
    stages = parser.parseFile(filename);

    for (int i = 0; i < 4; i++) {
        Point positionTL = {20, 875 + static_cast<float>(i) * 25};
        racerStart.emplace_back(positionTL);
    }
}

std::shared_ptr<AbstractElement> Map::getCollisionElement(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight, Point &playerCenter) {
    for (auto &stage : stages) {
        for (auto &element : stage->elements) {
            bool isCollision = element->intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight, playerCenter);
            if (isCollision) {
                return element;
            }
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<AbstractElement>> Map::getElementsInStage(int currentStage) { return stages[currentStage]->elements; }

Point& Map::getStartPointByID(int id) { return racerStart[id]; }
