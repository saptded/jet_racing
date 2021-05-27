#pragma once

#include "Element.h"
#include "Logger.h"
#include "StageStruct.h"

class ParserXML {
public:
    ParserXML() { init_logger(); }
    ~ParserXML() = default;
    std::vector<std::shared_ptr<Stage>> parseFileXML(const std::string &filename);

private:
    class ParserImpl;
    std::unique_ptr<ParserImpl> pImpl;
};
