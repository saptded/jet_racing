#pragma once

#include <memory>
#include <vector>

#include "AbstractElement.h"

struct Stage {
    std::vector<std::shared_ptr<AbstractElement>> elements;
};
