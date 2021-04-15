#include <gtest/gtest.h>

#include "Map.h"
#include "Element.h"

#define FILENAME "../map.txt"

TEST(TestParseMap, Map) {
    Map map(FILENAME);
    Block block;
    Stage stage;

    EXPECT_FALSE(block.elements.empty());
    EXPECT_FALSE(stage.blocks.empty());
}
