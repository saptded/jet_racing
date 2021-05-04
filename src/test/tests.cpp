//
// Created by dark0ghost on 14.04.2021.
//
#include <gtest/gtest.h>
#include <DataGame.hpp>
#include <GameClient.cpp>


TEST(stress_test, tests_input) {
    auto client = GameClient();
    DataGame data = DataGame(std::vector<Position>());
    client.send_data(data);
    ASSERT_EQ(data.status, 200);

}

int main(int argc, char **argv){
    ::testing::GTEST_FLAG(catch_exceptions) = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}