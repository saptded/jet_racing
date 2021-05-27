#include <cmath>
#include <gtest/gtest.h>

#include "Element.h"
#include "MathCalculation.h"

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

TEST(TestIntersection, PlayerToRectangleNoIntersect) {
    Rectangle upLeftRect({1, 4}, {3, 1}, {2, 2.5});
    Rectangle upRightRect({3, 3}, {9, 1}, {6, 2});
    Rectangle rightRect({7, 8}, {11, 4}, {9, 6});
    Rectangle bottomRect({4, 11}, {8, 7}, {6, 9});
    Rectangle bottomLeftRect({1, 9}, {3, 5}, {2, 7});

    std::vector<Rectangle> rectanglesTest{upLeftRect, upRightRect, rightRect, bottomRect, bottomLeftRect};

    std::vector<playerPosition> playerCoordinates = getPlayerCoordinates();

    for (auto &rect : rectanglesTest) {
        EXPECT_FALSE(rect.intersect(playerCoordinates[0].playerTL, playerCoordinates[0].playerTR, playerCoordinates[0].playerBL, playerCoordinates[0].playerBR));
        EXPECT_FALSE(rect.intersect(playerCoordinates[1].playerTL, playerCoordinates[1].playerTR, playerCoordinates[1].playerBL, playerCoordinates[1].playerBR));

    }
}

TEST(TestIntersection, PlayerToRectangleIntersect) {
    Rectangle upRect({1, 5}, {7, 1}, {4, 3});
    Rectangle rightRect({3, 9}, {9, 1}, {6, 5});
    Rectangle bottomRect({1, 9}, {9, 5}, {5, 7});
    Rectangle leftRect({1, 9}, {5, 1}, {3, 5});

    std::vector<Rectangle> rectanglesTest{upRect, rightRect, bottomRect, leftRect};

    std::vector<playerPosition> playerCoordinates = getPlayerCoordinates();

    for (auto &rect : rectanglesTest) {
        EXPECT_TRUE(rect.intersect(playerCoordinates[0].playerTL, playerCoordinates[0].playerTR, playerCoordinates[0].playerBL, playerCoordinates[0].playerBR));
        EXPECT_TRUE(rect.intersect(playerCoordinates[1].playerTL, playerCoordinates[1].playerTR, playerCoordinates[1].playerBL, playerCoordinates[1].playerBR));

    }
}

TEST(TestMath, CosineCalculation) {
    float cosineOfRightAngle = findCosine(3, 0, 0, -3);
    float cosineOfStraightAngle = findCosine(3, -3, 0, 0);
    float cosineOfZeroAngle = findCosine(3, 3, 0, 0);
    float cosineOfSixtyDegreeAngle = findCosine(-4, -4, 0, 6.9);

    EXPECT_EQ(cosineOfRightAngle, 0);
    EXPECT_EQ(cosineOfStraightAngle, -1);
    EXPECT_EQ(cosineOfZeroAngle, 1);
    EXPECT_EQ(std::round(cosineOfSixtyDegreeAngle * 10) / 10, 0.5);
}

TEST(TestMath, PointInZoneOfLine) {
    Line lineHorizontal({200, 200}, {400, 200}, {0, 0});
    Line lineVertical({300, 500}, {300, 100}, {0, 0});
    Line lineDiagonal({400, 100}, {200, 500}, {0, 0});
    std::vector<Line> lines{lineHorizontal, lineVertical, lineDiagonal};

    Point inZoneOne(350, 300);
    Point inZoneTwo(300, 101);
    Point inZoneThree(200, 300);
    std::vector<Point> pointsInZone{inZoneOne, inZoneTwo, inZoneThree};

    Point outZoneOne(1000, 950);
    Point outZoneTwo(450, 300);
    Point outZoneThree(199, 199);
    std::vector<Point> pointsOutZone{outZoneOne, outZoneTwo, outZoneThree};

    for (auto &in : pointsInZone) {
        for (auto &line : lines) {
            EXPECT_TRUE(isPointInZone(in, line._start, line._end));
        }
    }

    for (auto &out : pointsOutZone) {
        for (auto &line : lines) {
            EXPECT_FALSE(isPointInZone(out, line._start, line._end));
        }
    }
}
