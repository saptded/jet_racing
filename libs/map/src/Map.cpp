#include <memory>

#include "Map.h"

Map::Map(const std::string &filename) {
    stages = parser.parseFile(filename);
    for (int i = 0; i < 4; i++) {
        racerStart[i].first.x = 50;
        racerStart[i].first.y = 875 + static_cast<float>(i) * 50;
        racerStart[i].second.x = 80;
        racerStart[i].second.y = 887 + static_cast<float>(i) * 50;
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

std::pair<Point, Point> Map::getStartPointByID(int id) { return racerStart[id]; }
