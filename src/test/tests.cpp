//
// Created by dark0ghost on 14.04.2021.
//
#include <gtest/gtest.h>
#define test_jet_racing
#include "GameClient.hpp"
#include "serialization.h"

class Response{

};
class request{

    template<class name>
    static Response getRequest(name t){
        return Response();
     }
};

TEST(stress_test, tests_input) {
    auto client = GameClient<request>();
    auto ret  = client.getUpdates();
    ASSERT_EQ(ret, "200");
}

TEST(serialization_test, tests_input) {
    Position user = Position{"racer", "1", "2", "4"};
    std::string response = writeToJson(user);
    ASSERT_EQ(response, "{\"username\":\"racer\",\"x\":1,\"y\":2,\"z\":4}");
}
TEST(json_parser_test, tests_input) {

}



int main(int argc, char **argv){
    ::testing::GTEST_FLAG(catch_exceptions) = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}