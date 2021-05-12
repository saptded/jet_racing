#pragma once

#include <memory>
#include <vector>

#include "BlockStruct.h"

struct Stage {
    std::vector<std::shared_ptr<Block>> blocks;
};
