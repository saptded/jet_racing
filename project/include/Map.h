#ifndef PROJECT_INCLUDE_MAP_H_
#define PROJECT_INCLUDE_MAP_H_

#include <string>
#include <memory>
#include <vector>

#include "Element.h"
#include "BlockStruct.h"
#include "StageStruct.h"

class Map {
 public:
    Map() = default;
    explicit Map(const std::string& filename);
    ~Map() = default;

    void parseFile(const std::string& filename);
    void pushElementInBlock(Element& element);
    void pushBlockIntoStage();
    Element& getCollisionElement(Stage& stage, size_t pos_x, size_t pos_y);
    Stage& getCurrentStage(size_t pos_x, size_t pos_y);
 private:
    std::vector<std::shared_ptr<Element>> elements;
    Block block;
    Stage stage;
};

#endif  // PROJECT_INCLUDE_MAP_H_
