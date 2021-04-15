#include <iostream>
#include <memory>

#include "Map.h"

Map::Map(const std::string& filename) {
    parseFile(filename);
}

void Map::parseFile(const std::string &filename) {
    std::cout << "Parsing file" << std::endl;

    Point start = {0, 0};
    Point end = {0, 1};
    Line line(start, end);

    pushElementInBlock(line);

    pushBlockInStage();
}

void Map::pushElementInBlock(AbstractElement& element) {
    std::cout << "Push element into block while parsing file" << std::endl;
}

void Map::pushBlockInStage() {
    std::cout << "Push block into stage while parsing file" << std::endl;
}

std::vector<std::shared_ptr<AbstractElement>> Map::getDynamicElements(size_t pos_x, size_t pos_y) {
    std::cout << "Find dynamic elements and push into vector" << std::endl;
    std::vector<std::shared_ptr<AbstractElement>> dynamicElems;
    return dynamicElems;
}

AbstractElement& Map::getCollisionElement(size_t pos_x, size_t pos_y) {
    stage = getCurrentStage(pos_x, pos_y);

    Point start = {0, 0};
    Point end = {0, 1};
    static Line line(start, end);

    std::cout << "Using car's position calculate the element player should collide with" << std::endl;

    return line;
}

Stage& Map::getCurrentStage(size_t pos_x, size_t pos_y) {
    std::cout << "Using car's position calculate in what stage he is" << std::endl;
    return stage;
}
