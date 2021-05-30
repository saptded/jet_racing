#include <cmath>
#include <gtest/gtest.h>

#include "mechanicalValues.hpp"
#include "racer.hpp"
#include "racerController.hpp"

constexpr float eps = std::numeric_limits<float>::epsilon();
constexpr float epsHard = 0.001;

TEST(TestChangeRotationSpeed, TestRacerLeftRotation) {
    RacerController controller;
    Racer racer;

    controller.changeRotationSpeed(Command::left, racer);

    EXPECT_TRUE(racer._rotationSpeed.speedX > 0);
    EXPECT_TRUE(racer._rotationSpeed.speedY < eps);
    EXPECT_TRUE(std::abs(racer._rotationSpeed.speedX - DEFAULT_ROTATION_ACCELERATE) < eps);
}

TEST(TestChangeRotationSpeed, TestRacerLeftRotationExtra) {
    RacerController controller;
    Racer racer;
    float extraAccelerate = 0.5;

    controller.changeRotationSpeed(Command::left, racer, extraAccelerate);

    EXPECT_TRUE(std::abs(racer._rotationSpeed.speedX - DEFAULT_ROTATION_ACCELERATE) < eps + extraAccelerate);
}

TEST(TestChangeRotationSpeed, TestRacerRightRotation) {
    RacerController controller;
    Racer racer;

    controller.changeRotationSpeed(Command::right, racer);

    EXPECT_TRUE(racer._rotationSpeed.speedY > 0);
    EXPECT_TRUE(racer._rotationSpeed.speedX < eps);
    EXPECT_TRUE(std::abs(racer._rotationSpeed.speedY - DEFAULT_ROTATION_ACCELERATE) < eps);
}

TEST(TestChangeRotationSpeed, TestRacerRightRotationExtra) {
    RacerController controller;
    Racer racer;
    float extraAccelerate = 0.5;

    controller.changeRotationSpeed(Command::right, racer);

    EXPECT_TRUE(std::abs(racer._rotationSpeed.speedY - DEFAULT_ROTATION_ACCELERATE) < eps + extraAccelerate);
}

TEST(TestChangeRotationSpeed, TestRacerNoneRotation) {
    RacerController controller;
    Racer racer;

    controller.changeRotationSpeed(Command::none, racer);

    EXPECT_TRUE(racer._rotationSpeed.speedY < eps);
    EXPECT_TRUE(racer._rotationSpeed.speedX < eps);
}

TEST(TestChangeSpeed, TestRacerAccleratingX) {
    RacerController controller;
    Racer racer;

    racer._rotation = 0;
    controller.changeSpeed(racer);

    EXPECT_TRUE(std::abs(racer._speed.speedX - std::copysignf(DEFAULT_SPEED_ACCELERATE, racer._speed.speedX)) < epsHard);
    EXPECT_TRUE(racer._speed.speedY < eps);
}

TEST(TestChangeSpeed, TestRacerAccleratingY) {
    RacerController controller;
    Racer racer;

    racer._rotation = 90;
    controller.changeSpeed(racer);

    EXPECT_TRUE(std::abs(racer._speed.speedY - std::copysignf(DEFAULT_SPEED_ACCELERATE, racer._speed.speedY)) < epsHard);
    EXPECT_TRUE(racer._speed.speedX < eps);
}

TEST(TestChangeSpeed, TestRacerAccleratingXY) {
    RacerController controller;
    Racer racer;

    racer._rotation = 45;
    controller.changeSpeed(racer);

    EXPECT_TRUE(std::abs(racer._speed.speedY - std::copysignf(std::sin((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE, racer._speed.speedY)) <
                epsHard);
    EXPECT_TRUE(std::abs(racer._speed.speedX - std::copysignf(std::cos((racer._rotation * M_PI) / 180) * DEFAULT_SPEED_ACCELERATE, racer._speed.speedX)) <
                epsHard);
}

TEST(TestChangeSpeed, TestRacerAccleratingMax) {
    RacerController controller;
    Racer racer;

    racer._rotation = 45;
    for (size_t i = 0; i < 1000; ++i) {
        controller.changeSpeed(racer);
    }

    EXPECT_TRUE(std::abs(racer._speed.speedY - std::copysignf(DEFAULT_MAX_SPEED, racer._speed.speedY)) < OVER_SPEED_DECEL);
    EXPECT_TRUE(std::abs(racer._speed.speedX - std::copysignf(DEFAULT_MAX_SPEED, racer._speed.speedX)) < OVER_SPEED_DECEL);
}

TEST(TestChangeSpeed, TestRacerAccleratingStop) {
    RacerController controller;
    Racer racer;

    for (size_t i = 0; i < 1000; ++i) {
        controller.changeSpeed(racer);
    }
    controller.changeSpeed(racer, true);

    EXPECT_TRUE(racer._speed.speedX < eps);
    EXPECT_TRUE(racer._speed.speedY < eps);
}
