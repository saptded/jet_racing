#include <gtest/gtest.h>

#include "Element.h"

TEST(TestIntersection, PlayerToLineNoIntersect) {
    Line horizontalLine({1, 1}, {5, 1}, {0, 0});
    Line verticalLine({1, 2}, {1, 3}, {0, 0});
    Line diagonalLine({6, 5}, {2, 7}, {0, 0});

    Point playerTL{2, 2};
    Point playerTR{4, 2};
    Point playerBL{4, 5};
    Point playerBR{2, 5};

    EXPECT_FALSE(horizontalLine.intersect(playerTL, playerTR, playerBL, playerBR));
    EXPECT_FALSE(verticalLine.intersect(playerTL, playerTR, playerBL, playerBR));
    EXPECT_FALSE(diagonalLine.intersect(playerTL, playerTR, playerBL, playerBR));
}

TEST(TestIntersection, PlayerToLineIntersect) {
    Line horizontalLine({1, 1}, {5, 1}, {0, 0});
    Line verticalLine({1, 2}, {1, 3}, {0, 0});
    Line diagonalLine({6, 5}, {2, 7}, {0, 0});

    Point playerTL{1, 1};
    Point playerTR{4, 1};
    Point playerBL{4, 6};
    Point playerBR{1, 6};

    EXPECT_TRUE(horizontalLine.intersect(playerTL, playerTR, playerBL, playerBR));
    EXPECT_TRUE(verticalLine.intersect(playerTL, playerTR, playerBL, playerBR));
    EXPECT_TRUE(diagonalLine.intersect(playerTL, playerTR, playerBL, playerBR));
}

