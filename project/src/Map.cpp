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
    pushBlockIntoStage();
}

void Map::pushElementInBlock(Element& element) {
    std::cout << "Push element into block while parsing file" << std::endl;
}

void Map::pushBlockIntoStage() {
    std::cout << "Push block into stage while parsing file" << std::endl;
}
