//
// Created by dark0ghost on 14.04.2021.
//
#include <gtest/gtest.h>
#include "../data_structs/DataGame.hpp"

import game_server;
import clent;


TEST(stress_test, tests_input) {
    auto server = GameServer();
    server.start_server();

    auto client = GameClient();
    DataGame data = {{"status", "server"}};
    auto res = client.send_data()
    ASSERT_EQ(res.status, 200);

}

int main(int argc, char **argv){
    ::testing::GTEST_FLAG(catch_exceptions) = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}