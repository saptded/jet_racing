#ifndef PROJECT_INCLUDE_MAP_H_
#define PROJECT_INCLUDE_MAP_H_

#include <string>
#include <memory>
#include <vector>

#include "Element.h"
#include "BlockStruct.h"
#include "StageStruct.h"
#include "Parser.h"

class Map {
 public:
    Map() = default;
    explicit Map(const std::string &filename);
    ~Map() = default;

//    void parseFile(const std::string& filename);
//    void pushElementInBlock(AbstractElement &element);
//    void pushBlockInStage();
    std::vector<std::shared_ptr<AbstractElement>> getDynamicElements(size_t pos_x, size_t pos_y);
    AbstractElement &getCollisionElement(Point posStart, Point posEnd, Point posCenter);
//    Stage &getCurrentStage(Point posStart, Point posEnd, Point posCenter);
 private:
    std::vector<std::shared_ptr<AbstractElement>> elements;
    std::vector<std::shared_ptr<AbstractElement>> dynamicElements;
    Block block;
    Stage stage;
    Parser parser;
    std::vector<std::shared_ptr<Stage>> stages;
};

#endif  // PROJECT_INCLUDE_MAP_H_
