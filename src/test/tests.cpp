//
// Created by dark0ghost on 14.04.2021.
//
#include <gtest/gtest.h>
#define test_jet_racing
#include "GameClient.hpp"
#include <GameServer.hpp>

class Response{

};
class request{

    template<class name>
    static Response getRequest(name t){

}
};

TEST(stress_test, tests_input) {
    auto client = GameClient<request>();
    auto ret  = client.getUpdates();
    ASSERT_EQ(ret, "200");
}


int main(int argc, char **argv){
    ::testing::GTEST_FLAG(catch_exceptions) = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}