#pragma once

#include "response.hpp"
#include "mechanicalValues.hpp"

#include <memory>

class GameViewer {
public:
    virtual void render(std::shared_ptr<Response> data) = 0;

    virtual Command handleButtonEvent() = 0;

    virtual void close() = 0;

protected:
    int stage = 0;
};
