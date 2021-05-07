#ifndef PROJECT_INCLUDE_STAGESTRUCT_H_
#define PROJECT_INCLUDE_STAGESTRUCT_H_

#include <memory>
#include <vector>

#include "BlockStruct.h"

typedef struct Stage {
    std::vector<std::shared_ptr<Block>> blocks;
} Stage;

#endif  // PROJECT_INCLUDE_STAGESTRUCT_H_
