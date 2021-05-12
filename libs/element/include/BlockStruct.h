#pragma once

#include <memory>
#include <vector>

#include "AbstractElement.h"

struct Block {
    std::vector<std::shared_ptr<AbstractElement>> elements;
};
