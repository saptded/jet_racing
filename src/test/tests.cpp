//
// Created by dark0ghost on 14.04.2021.
//
#include <gtest/gtest.h>
#define test_jet_racing
#include "GameClient.hpp"
#include "serialization.h"
#include <GameServer.hpp>
#include <string>
#include <variant>

class UrlBuildr{

};

class Response {
    std::string testLocal;
public:
    Response set_body(std::string test) {
        testLocal = test;
        return *this;
    }
};

class request{

    template<class name>
    static Response getRequest(name t){
        return Response();
     }
};



TEST(stress_test, tests_input) {
    auto client = GameClient<request, UrlBuildr>();
    std::vector<Position> ret  = client.getUpdates<Response>();
    ASSERT_EQ(ret[0].username, "200");
}

TEST(serialization_test, tests_input) {
    Position user = Position{"racer", "1", "2", "4"};
    std::string response = writeToJson(user);
    ASSERT_EQ(response, R"({"username":"racer","x":"1","y":"2","rotation":"4","speed":0.000000,"stage":0,"isFinished":0})");
}

TEST(unit_test, ping_server_test) {
    auto server = GameServer();
    std::string  result = server.ping();
    ASSERT_EQ(result, "{\"name\":\"jet_racing\"}");
}

TEST(unit_test, add_server_test) {
    auto server = GameServer();
    std::string username = "user";
    std::string id = server.addUser(username);
    ASSERT_EQ(id,R"({"id":0})");
}

TEST(unit_test, set_server_test) {
    auto server = GameServer();
    std::string username = "user";
    std::string id = server.addUser(username);
    std::string res = server.setNewPosition("0","1","2","3",1.001,2,true);
    ASSERT_EQ(res,R"({"status": "ok"})");
}

TEST(unit_test, render_and_get_server_test) {
    auto server = GameServer();
    std::string username = "user";
    std::string id = server.addUser(username);
    std::string res = server.setNewPosition("0","1","2","3",1.001,2,true);
    auto t = server.sendNewPosition();
    ASSERT_EQ(t,R"([{"username":"user","x":"1","y":"2","rotation":"3","speed":1.001000,"stage":2,"isFinished":1}])");
}

TEST(unit_test, error_set_server_test) {
    auto server = GameServer();
    std::string username = "user";
    std::string id = server.addUser(username);
    std::string res = server.setNewPosition("-1","1","2","3",1.001,2,true);
    ASSERT_EQ(res,R"({"status": "fail: name error"})");
}





int main(int argc, char **argv){
    ::testing::GTEST_FLAG(catch_exceptions) = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}