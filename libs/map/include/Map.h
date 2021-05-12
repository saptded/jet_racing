#pragma once

#include <memory>
#include <string>
#include <vector>

#include "BlockStruct.h"
#include "Element.h"
#include "Parser.h"
#include "StageStruct.h"

class Map {
public:
    Map() = default;
    explicit Map(const std::string &filename);
    ~Map() = default;

    //    std::vector<std::shared_ptr<AbstractElement>> getDynamicElements();
    std::shared_ptr<AbstractElement> getCollisionElement(Point playerTopLeft, Point playerTopRight, Point playerBottomLeft, Point playerBottomRight);

private:
    // TODO во время парсинга запихивать элементы в ектор элементов, вектор динамических элементов не нужен
    std::vector<std::shared_ptr<AbstractElement>> elements;
    //    std::vector<std::shared_ptr<AbstractElement>> dynamicElements;
    Parser parser;
    std::vector<std::shared_ptr<Stage>> stages;
};
