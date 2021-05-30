#include <cmath>
#include <gtest/gtest.h>

#include "mechanicalValues.hpp"
#include "racer.hpp"
#include "racerController.hpp"

constexpr float eps = std::numeric_limits<float>::epsilon();
constexpr float epsHard = 0.001;

TEST(TestUpdatePosition, TestRacerUpdatePositionX) {
    RacerController controller;
    Racer racer;

    racer._rotation = 0;
    controller.changeSpeed(racer);
    controller.updatePosition(racer);

    EXPECT_TRUE(std::abs(racer._position.first.x - DEFAULT_SPEED_ACCELERATE) <= epsHard);
    EXPECT_TRUE(std::abs(racer._position.second.x - DEFAULT_SPEED_ACCELERATE) <= epsHard + racer._width);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.x - DEFAULT_SPEED_ACCELERATE) <= epsHard);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.x - DEFAULT_SPEED_ACCELERATE) <= epsHard + racer._width);
    EXPECT_TRUE(std::abs(racer._position.first.y) <= eps);
    EXPECT_TRUE(std::abs(racer._position.second.y) <= eps + racer._height);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.y) <= eps + racer._height);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.y) <= eps);

    EXPECT_TRUE(std::abs(racer._center.x - DEFAULT_SPEED_ACCELERATE - racer._origin.x) <= epsHard);
    EXPECT_TRUE(std::abs(racer._center.y - racer._origin.y) <= eps);
}

TEST(TestUpdatePosition, TestRacerUpdatePositionY) {
    RacerController controller;
    Racer racer;

    racer._rotation = 90;
    controller.changeSpeed(racer);
    controller.updatePosition(racer);

    EXPECT_TRUE(std::abs(racer._position.first.y + DEFAULT_SPEED_ACCELERATE) <= epsHard);
    EXPECT_TRUE(std::abs(racer._position.second.y + DEFAULT_SPEED_ACCELERATE) <= epsHard + racer._height);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.y + DEFAULT_SPEED_ACCELERATE) <= epsHard + racer._height);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.y + DEFAULT_SPEED_ACCELERATE) <= epsHard);
    EXPECT_TRUE(std::abs(racer._position.first.x) <= eps);
    EXPECT_TRUE(std::abs(racer._position.second.x) <= eps + racer._width);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.x) <= eps);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.x) <= eps + racer._width);

    EXPECT_TRUE(std::abs(racer._center.y - racer._origin.y + DEFAULT_SPEED_ACCELERATE) <= epsHard);
    EXPECT_TRUE(std::abs(racer._center.x - racer._origin.x) <= epsHard);
}

TEST(TestUpdatePosition, TestRacerUpdatePositionXY) {
    RacerController controller;
    Racer racer;

    racer._rotation = 45;
    controller.changeSpeed(racer);
    controller.updatePosition(racer);

    EXPECT_TRUE(std::abs(racer._position.first.x - std::cos((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE) <= epsHard);
    EXPECT_TRUE(std::abs(racer._position.second.x - std::cos((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE) <= epsHard + racer._width);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.x - std::cos((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE) <= epsHard);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.x - std::cos((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE) <= epsHard + racer._width);
    EXPECT_TRUE(std::abs(racer._position.first.y + std::sin((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE) <= epsHard);
    EXPECT_TRUE(std::abs(racer._position.second.y + std::sin((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE) <= epsHard + racer._height);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.y + std::sin((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE) <= epsHard + racer._height);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.y + std::sin((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE) <= epsHard);

    EXPECT_TRUE(std::abs(racer._center.x - std::cos((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE - racer._origin.x) <= epsHard);
    EXPECT_TRUE(std::abs(racer._center.y - racer._origin.y + std::sin((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE) <= epsHard);
}

TEST(TestUpdatePosition, TestRacerUpdatePositionNew) {
    RacerController controller;
    Racer racer;

    float newX = 20;
    float newY = newX;
    Point newCenterPosition = {newX, newY};

    controller.updatePosition(racer, newCenterPosition);

    EXPECT_TRUE(std::abs(racer._position.first.x - newX + racer._origin.x) <= epsHard);
    EXPECT_TRUE(std::abs(racer._position.second.x - newX + racer._origin.x) <= epsHard + racer._width);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.x - newX + racer._origin.x) <= epsHard);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.x - newX + racer._origin.x) <= epsHard + racer._width);
    EXPECT_TRUE(std::abs(racer._position.first.y - newY + racer._origin.y) <= epsHard);
    EXPECT_TRUE(std::abs(racer._position.second.y - newY + racer._origin.y) <= epsHard + racer._height);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.y - newY + racer._origin.y) <= epsHard + racer._height);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.y - newY + racer._origin.y) <= epsHard);

    EXPECT_TRUE(std::abs(racer._center.x - newX) <= epsHard);
    EXPECT_TRUE(std::abs(racer._center.y - newY) <= epsHard);
}
