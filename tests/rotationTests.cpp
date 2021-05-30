#include <cmath>
#include <gtest/gtest.h>

#include "mechanicalValues.hpp"
#include "racer.hpp"
#include "racerController.hpp"

constexpr float eps = std::numeric_limits<float>::epsilon();
constexpr float epsHard = 0.001;

TEST(TestUpdatePosition, TestRacerUpdateRotation) {
    RacerController controller;
    Racer racer;

    float _width = 2;
    float _height = 1;

    racer._width = 2;
    racer._height = 1;

    racer._rotation = 0;
    racer._speed = {0, 0};
    racer._rotationSpeed = {0, 0};

    racer._position = std::make_pair(Point{0, 0}, Point{_width, _height});       // top left / bottom right
    racer._positionExtra = std::make_pair(Point{0, _height}, Point{_width, 0});  // bottom left / top right
    racer._center = {_width / 2, _height / 2};
    racer._origin = {_width / 2, _height / 2};

    racer._rotation = 90;
    controller.updateRotation(racer);

    EXPECT_TRUE(std::abs(racer._position.first.x - 0.5) < eps);
    EXPECT_TRUE(std::abs(racer._position.first.y - 1.5) < eps);
    EXPECT_TRUE(std::abs(racer._position.second.x - 1.5) < eps);
    EXPECT_TRUE(std::abs(racer._position.second.y + 0.5) < eps);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.x - 1.5) < eps);
    EXPECT_TRUE(std::abs(racer._positionExtra.first.y - 1.5) < eps);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.x - 0.5) < eps);
    EXPECT_TRUE(std::abs(racer._positionExtra.second.y + 0.5) < eps);
}
