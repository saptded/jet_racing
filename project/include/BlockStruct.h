#ifndef PROJECT_INCLUDE_BLOCKSTRUCT_H_
#define PROJECT_INCLUDE_BLOCKSTRUCT_H_

#include <memory>
#include <vector>

#include "Element.h"

typedef struct Block {
    std::vector<std::shared_ptr<Element>> elements;
} Block;


#endif  // PROJECT_INCLUDE_BLOCKSTRUCT_H_
