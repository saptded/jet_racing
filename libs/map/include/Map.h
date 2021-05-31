#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Element.h"
#include "Parser.h"
#include "StageStruct.h"

class Map {
public:
    Map() = default;
    explicit Map(const std::string &filename);
    ~Map() = default;

    std::vector<std::shared_ptr<AbstractElement>> getElementsInStage(int currentStage);
    std::shared_ptr<AbstractElement> getCollisionElement(Point &playerTopLeft, Point &playerTopRight, Point &playerBottomLeft, Point &playerBottomRight, Point &playerCenter, int currentStage);
    Point& getStartPointByID(int id);

private:
    Parser parser;
    std::vector<std::shared_ptr<Stage>> stages;
    std::vector<Point> racerStart;
};
