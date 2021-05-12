#pragma once

#include "BlockStruct.h"
#include "Element.h"
#include "StageStruct.h"

class Parser {
public:
    Parser() = default;
    ~Parser() = default;
    std::vector<std::shared_ptr<Stage>> parseFile(const std::string &filename);
};
