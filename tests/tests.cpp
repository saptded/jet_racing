#include <gtest/gtest.h>

#include "Element.h"

struct playerPosition {
    Point playerTL;
    Point playerTR;
    Point playerBL;
    Point playerBR;
};

std::vector<playerPosition> getPlayerCoordinates() {
    std::vector<playerPosition> playerCoordinates;

    playerPosition playerOrthogonal = {Point(2, 2), Point(5, 2), Point(5, 6), Point(2, 6)};
    playerPosition playerAtAngle = {Point(4, 2), Point(8, 5), Point(6,7), Point(2, 4)};

    playerCoordinates.push_back(playerOrthogonal);
    playerCoordinates.push_back(playerAtAngle);

    return playerCoordinates;
}

TEST(TestIntersection, PlayerToLineNoIntersect) {
    Line upLineHorizontal({1, 1}, {6, 1}, {0, 0});
    Line bottomLineHorizontal({1, 8}, {9, 8}, {0, 0});
    Line leftLineVertical({1, 2}, {1, 6}, {0, 0});
    Line rightLineVertical({7, 1}, {7, 3}, {0, 0});
    Line rightLineDiagonal({5, 1}, {8, 4}, {0, 0});
    Line leftLineDiagonal({1, 4}, {2, 8}, {0, 0});

    std::vector<Line> linesTest{upLineHorizontal, bottomLineHorizontal, leftLineVertical, rightLineVertical, rightLineDiagonal, leftLineDiagonal};

    std::vector<playerPosition> playerCoordinates = getPlayerCoordinates();

    for (auto &line : linesTest) {
        EXPECT_FALSE(line.intersect(playerCoordinates[0].playerTL, playerCoordinates[0].playerTR, playerCoordinates[0].playerBL, playerCoordinates[0].playerBR));
        EXPECT_FALSE(line.intersect(playerCoordinates[1].playerTL, playerCoordinates[1].playerTR, playerCoordinates[1].playerBL, playerCoordinates[1].playerBR));
    }
}

TEST(TestIntersection, PlayerToLineIntersect) {
    Line upLineHorizontal({1, 2}, {7, 2}, {0, 0});
    Line leftLineVertical({2, 0}, {2, 8}, {0, 0});
    Line rightLineDiagonal({4, 1}, {9, 6}, {0, 0});
    Line leftLineDiagonal({2, 6}, {10, 8}, {0, 0});

    std::vector<Line> linesTest{upLineHorizontal, leftLineVertical, rightLineDiagonal, leftLineDiagonal};

    std::vector<playerPosition> playerCoordinates = getPlayerCoordinates();

    for (auto &line : linesTest) {
        EXPECT_TRUE(line.intersect(playerCoordinates[0].playerTL, playerCoordinates[0].playerTR, playerCoordinates[0].playerBL, playerCoordinates[0].playerBR));
        EXPECT_TRUE(line.intersect(playerCoordinates[1].playerTL, playerCoordinates[1].playerTR, playerCoordinates[1].playerBL, playerCoordinates[1].playerBR));
    }
}

