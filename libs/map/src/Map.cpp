#include <memory>

#include "Map.h"

constexpr float initPlayerPointX = 20;
constexpr float initPlayerPointY = 875;
constexpr float kDistance = 25;

Map::Map(const std::string &filename) {
    stages = parser.parseFileXML(filename);

    for (int i = 0; i < 4; i++) {
        Point positionTL = {initPlayerPointX, initPlayerPointY + static_cast<float>(i) * kDistance};
        racerStart.emplace_back(positionTL);
    }
}

std::shared_ptr<AbstractElement> Map::getCollisionElement(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight) {
    for (auto &stage : stages) {
        for (auto &element : stage->elements) {
            bool isCollision = element->intersect(playerTopLeft, playerTopRight, playerBottomLeft, playerBottomRight);
            if (isCollision) {
                return element;
            }
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<AbstractElement>> Map::getElementsInStage(int currentStage) { return stages[currentStage]->elements; }

Point &Map::getStartPointByID(int id) { return racerStart[id]; }
