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
    playerPosition playerAtAngle = {Point(4, 2), Point(8, 6), Point(6, 8), Point(2, 4)};

    playerCoordinates.push_back(playerOrthogonal);
    playerCoordinates.push_back(playerAtAngle);

    return playerCoordinates;
}

TEST(TestIntersection, PlayerToLineNoIntersect) {
    Line upLineHorizontal({1, 1}, {6, 1}, {0, 0});
    Line bottomLineHorizontal({1, 9}, {9, 9}, {0, 0});
    Line leftLineVertical({1, 2}, {1, 6}, {0, 0});
    Line rightLineVertical({7, 1}, {7, 3}, {0, 0});
    Line rightLineDiagonal({5, 1}, {8, 5}, {0, 0});
    Line leftLineDiagonal({1, 4}, {2, 8}, {0, 0});

    std::vector<Line> linesTest{upLineHorizontal, bottomLineHorizontal, leftLineVertical, rightLineVertical, rightLineDiagonal, leftLineDiagonal};

    std::vector<playerPosition> playerCoordinates = getPlayerCoordinates();

    for (auto &line : linesTest) {
        EXPECT_FALSE(
            line.intersect(playerCoordinates[0].playerTL, playerCoordinates[0].playerTR, playerCoordinates[0].playerBL, playerCoordinates[0].playerBR));
        EXPECT_FALSE(
            line.intersect(playerCoordinates[1].playerTL, playerCoordinates[1].playerTR, playerCoordinates[1].playerBL, playerCoordinates[1].playerBR));
    }
}

TEST(TestIntersection, PlayerToLineIntersect) {
    Line upLineHorizontal({1, 2}, {7, 2}, {0, 0});
    Line leftLineVertical({2, 0}, {2, 8}, {0, 0});
    Line rightLineDiagonal({11, 10}, {3.5, 0}, {0, 0});
    Line leftLineDiagonal({0, 5}, {8, 9}, {0, 0});

    std::vector<Line> linesTest{upLineHorizontal, leftLineVertical, rightLineDiagonal, leftLineDiagonal};

    std::vector<playerPosition> playerCoordinates = getPlayerCoordinates();

    for (auto &line : linesTest) {
        EXPECT_TRUE(line.intersect(playerCoordinates[0].playerTL, playerCoordinates[0].playerTR, playerCoordinates[0].playerBL, playerCoordinates[0].playerBR));
        EXPECT_TRUE(line.intersect(playerCoordinates[1].playerTL, playerCoordinates[1].playerTR, playerCoordinates[1].playerBL, playerCoordinates[1].playerBR));
    }
}

TEST(TestIntersection, PlayerToArcNoIntersect) {
    Arc upArcToTheLeft({0, 4}, {6, 4}, {3, 4});
    Arc upArcToTheRight({1, 4}, {7, 4}, {4, 4});
    Arc bottomArcToTheLeft({6, 4}, {0, 4}, {3, 4});
    Arc bottomArcToTheRight({7, 4}, {1, 4}, {4, 4});
    Arc leftArcToTheLeft({3, 7}, {3, 1}, {3, 4});
    Arc leftArcToTheRight({4, 7}, {4, 1}, {4, 4});
    Arc rightArcToTheLeft({3, 1}, {3, 7}, {3, 4});
    Arc rightArcToTheRight({4, 1}, {4, 7}, {4, 4});

    std::vector<Arc> linesTestOrthPlayer{upArcToTheLeft,   upArcToTheRight,   bottomArcToTheLeft, bottomArcToTheRight,
                                         leftArcToTheLeft, leftArcToTheRight, rightArcToTheLeft,  rightArcToTheRight};

    Arc upArcAbove({1, 4}, {9, 4}, {5, 4});
    Arc upArcBelow({1, 5}, {9, 5}, {5, 5});
    Arc bottomArcAbove({9, 4}, {1, 4}, {5, 4});
    Arc bottomArcTBelow({9, 5}, {1, 5}, {5, 5});
    Arc leftArcAbove({5, 8}, {5, 0}, {5, 4});
    Arc leftArcBelow({5, 9}, {5, 1}, {5, 5});
    Arc rightArcAbove({5, 0}, {5, 8}, {5, 4});
    Arc rightArcBelow({5, 1}, {5, 9}, {5, 5});

    std::vector<Arc> linesTestAtAnglePlayer{upArcAbove, upArcBelow, bottomArcAbove, bottomArcTBelow, leftArcAbove, leftArcBelow, rightArcAbove, rightArcBelow};

    std::vector<playerPosition> playerCoordinates = getPlayerCoordinates();

    for (auto &line : linesTestOrthPlayer) {
        EXPECT_FALSE(
            line.intersect(playerCoordinates[0].playerTL, playerCoordinates[0].playerTR, playerCoordinates[0].playerBL, playerCoordinates[0].playerBR));
    }

    for (auto &line : linesTestAtAnglePlayer) {
        EXPECT_FALSE(
            line.intersect(playerCoordinates[1].playerTL, playerCoordinates[1].playerTR, playerCoordinates[1].playerBL, playerCoordinates[1].playerBR));
    }
}

TEST(TestIntersection, PlayerToArcIntersect) {
    Arc upArc({2, 2}, {5, 2}, {3.5, 2});
    Arc bottomArc({5, 6}, {2, 6}, {3.5, 6});
    Arc rightArc({5, 2}, {5, 6}, {5, 4});
    Arc leftArc({2, 6}, {2, 2}, {2, 4});
    Arc topLeftArc({2, 6}, {5, 2}, {3.5, 4});
    Arc topRightArc({2, 2}, {5, 6}, {3.5, 4});
    Arc bottomLeftArc({5, 6}, {2, 2}, {3.5, 4});
    Arc bottomRightArc({5, 2}, {2, 6}, {3.5, 4});

    std::vector<Arc> arcsTestOrthPlayer{upArc, bottomArc, rightArc, leftArc, topLeftArc, topRightArc, bottomLeftArc, bottomRightArc};

    Arc upArcDiagonal({2, 4}, {6, 4}, {4, 4});
    Arc bottomArcDiagonal({8, 6}, {4, 6}, {6, 6});
    Arc rightArcDiagonal({5, 3}, {5, 9}, {5, 6});
    Arc leftArcDiagonal({6, 8}, {6, 0}, {6, 4});
    Arc topLeftArcDiagonal({6, 8}, {4, 2}, {5, 5});
    Arc topRightArcDiagonal({2, 4}, {5, 6}, {5, 5});
    Arc bottomLeftArcDiagonal({4, 2}, {6, 8}, {5, 5});
    Arc bottomRightArcDiagonal({8, 6}, {2, 4}, {5, 5});

    std::vector<Arc> arcsTestAtAnglePlayer{upArcDiagonal, bottomArcDiagonal, rightArcDiagonal};

    std::vector<playerPosition> playerCoordinates = getPlayerCoordinates();

    for (auto &arc : arcsTestOrthPlayer) {
        EXPECT_TRUE(arc.intersect(playerCoordinates[0].playerTL, playerCoordinates[0].playerTR, playerCoordinates[0].playerBL, playerCoordinates[0].playerBR));
    }

    for (auto &arc : arcsTestAtAnglePlayer) {
        EXPECT_TRUE(arc.intersect(playerCoordinates[1].playerTL, playerCoordinates[1].playerTR, playerCoordinates[1].playerBL, playerCoordinates[1].playerBR));
    }
}
