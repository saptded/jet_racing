#ifndef JET_RACING_LIBS_PARSER_INCLUDE_PARSER_H_
#define JET_RACING_LIBS_PARSER_INCLUDE_PARSER_H_

#include "Element.h"
#include "BlockStruct.h"
#include "StageStruct.h"

class Parser {
 public:
    Parser() = default;
    ~Parser() = default;
    std::vector<std::shared_ptr<Stage>> parseFile(const std::string &filename);
};

#endif //JET_RACING_LIBS_PARSER_INCLUDE_PARSER_H_
