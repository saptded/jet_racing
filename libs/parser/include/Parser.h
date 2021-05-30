#pragma once

#include "Element.h"
#include "Logger.h"
#include "StageStruct.h"

class Parser {
public:
    Parser() { init_logger(); }
    ~Parser() = default;
    std::vector<std::shared_ptr<Stage>> parseFile(const std::string &filename);
};
