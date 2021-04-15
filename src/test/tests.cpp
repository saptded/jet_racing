//
// Created by dark0ghost on 14.04.2021.
//
#include <gtest/gtest.h>

import game_server;
import clent

TEST(stress_test, tests_input) {

}

int main(int argc, char **argv){
    ::testing::GTEST_FLAG(catch_exceptions) = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}