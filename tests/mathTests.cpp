#include <cmath>
#include <gtest/gtest.h>

#include "MathCalculation.h"
#include "mechanicalValues.hpp"
#include "racer.hpp"
#include "racerController.hpp"

constexpr float eps = std::numeric_limits<float>::epsilon();
constexpr float epsHard = 0.001;

TEST(TestIsPointOnTheLeftSideFromLine, TestRightSide) {
    Point point = {10, 10};
    Point start = {0, 0};
    Point end = {0, 100};

    EXPECT_FALSE(isPointOnTheLeftSideFromLine(point, start, end));
}

TEST(TestIsPointOnTheLeftSideFromLine, TestLeftSide) {
    Point point = {-10, 10};
    Point start = {0, 0};
    Point end = {0, 100};

    EXPECT_TRUE(isPointOnTheLeftSideFromLine(point, start, end));
}

TEST(TestIsPointOnTheLeftSideFromLine, TestDownSide) {  // down is "right"
    Point point = {10, 10};
    Point start = {0, 0};
    Point end = {100, 0};

    EXPECT_FALSE(isPointOnTheLeftSideFromLine(point, start, end));
}

TEST(TestIsPointOnTheLeftSideFromLine, TestUpSide) {
    Point point = {10, -10};
    Point start = {0, 0};
    Point end = {100, 0};

    EXPECT_TRUE(isPointOnTheLeftSideFromLine(point, start, end));
}

TEST(TestGetPushAngle, TestPushRight) {
    Point point = {10, 10};
    Point start = {0, 0};
    Point end = {0, 100};
    float lineAngle = 90;

    EXPECT_TRUE(getPushAngle(point, start, end, lineAngle) == 0);
}

TEST(TestGetPushAngle, TestPushLeft) {
    Point point = {-10, 10};
    Point start = {0, 0};
    Point end = {0, 100};
    float lineAngle = 90;

    EXPECT_TRUE(std::abs(getPushAngle(point, start, end, lineAngle)) == 180);
}

TEST(TestGetPushAngle, TestPushDown) {
    Point point = {10, 10};
    Point start = {0, 0};
    Point end = {100, 0};
    float lineAngle = 0;

    EXPECT_TRUE(getPushAngle(point, start, end, lineAngle) == -90);
}

TEST(TestGetPushAngle, TestPushUp) {
    Point point = {10, -10};
    Point start = {0, 0};
    Point end = {100, 0};
    float lineAngle = 0;

    EXPECT_TRUE(getPushAngle(point, start, end, lineAngle) == 90);
}

TEST(TestGetArcRadius, TestArcRadius1) {
    Point center = {0, 0};
    Point start = {0, 10};

    EXPECT_TRUE(getArcRadius(center, start) == 10);
}

TEST(TestGetArcRadius, TestArcRadius2) {
    Point center = {0, 0};
    Point start = {10, 0};

    EXPECT_TRUE(getArcRadius(center, start) == 10);
}

TEST(TestGetArcRadius, TestArcRadius3) {
    Point center = {0, 0};
    Point start = {-10, 0};

    EXPECT_TRUE(getArcRadius(center, start) == 10);
}

TEST(TestGetArcRadius, TestArcRadius4) {
    Point center = {0, 0};
    Point start = {0, -10};

    EXPECT_TRUE(getArcRadius(center, start) == 10);
}

TEST(TestGetArcPushAngle, TestArcPushAngle) {
    Racer racer;
    RacerController controller;
    racer._rotation = 90;
    controller.updateRotation(racer);
    controller.updatePosition(racer, Point{100, 30});

    Point center = {100, 0};
    Point start = {0, 0};

    std::vector<Point> pointsCurrent = {racer._position.first, racer._positionExtra.second, racer._positionExtra.first, racer._position.second,
                                        racer._center};  // 0, 1, 2, 3
    std::vector<Point> points;
    points.reserve(pointsCurrent.size());
    for (auto &prevPoint : pointsCurrent) {
        points.emplace_back(Point{static_cast<float>(prevPoint.x - racer._speed.speedX * 1.5), static_cast<float>(prevPoint.y - racer._speed.speedY * 1.5)});
    }
    std::map<uint8_t, float> distancesToArcCenter;
    uint8_t k = 0;
    float radius = getArcRadius(center, start);
    for (auto playerPoint : points) {
        auto distanceFromPointToArc = static_cast<float>(std::sqrt(std::pow(center.x - playerPoint.x, 2) + std::pow(center.y - playerPoint.y, 2)));
        distancesToArcCenter.insert(std::make_pair(k++, distanceFromPointToArc));
    }

    std::pair<float, bool> pushInfo = getArcPushAngle(distancesToArcCenter, radius, center, points);

    EXPECT_TRUE(pushInfo.first == 90);
    EXPECT_TRUE(pushInfo.second);
}
