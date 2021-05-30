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

class Response{
    std::string testLocal;
public:
   Response set_body(std::string test){
      testLocal = test;
       return *this;
  }

  [[nodiscard]]  std::string getTestResult() const{
      return testLocal;
  }
};
class CustomDict{
    std::vector<std::pair<std::string,std::string>> dict;
public:

    CustomDict(){
        auto username = std::pair<std::string,std::string>("username","test");
        auto x = std::pair<std::string,std::string>("x","1");
        auto y = std::pair<std::string,std::string>("y","1");
        auto rotation = std::pair<std::string,std::string>("rotation","1");
        auto stage = std::pair<std::string,std::string>("stage","1");
        auto speed = std::pair<std::string,std::string>("speed","1");
        auto isFinished = std::pair<std::string,std::string>("isFinished","1");
        auto id = std::pair<std::string,std::string>("id","0");

        dict = std::vector<std::pair<std::string,std::string>>();
        dict.push_back(username);
        dict.push_back(x);
        dict.push_back(y);
        dict.push_back(speed);
        dict.push_back(rotation);
        dict.push_back(stage);
        dict.push_back(isFinished);
        dict.push_back(id);
    }


   std::string operator[](const std::string& key){
        for(auto& d: dict){
            if (key == d.first){
                return d.second;
            }
        }
       return "error";
   }
};

class Header{
public:
    CustomDict query(){
        CustomDict dict;
        return dict;
    }
};

class RequestForServer{
public:
    Response create_response(){
        return Response();
    }

    Header header(){
        return Header();
    }

};

class request{

    template<class name>
    static Response getRequest(name t){
        return Response();
     }
};

CustomDict parse_query(CustomDict d){
    return d;
}

TEST(stress_test, tests_input) {
    auto client = GameClient<request>();
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
    auto* req = new RequestForServer();
    Response result = server.ping(req);
    ASSERT_EQ(result.getTestResult(), "{\"name\":\"jet_racing\"}");
}

TEST(unit_test, add_server_test) {
    auto server = GameServer();
    auto* req = new RequestForServer();
    Response id = server.addUser(req);
    ASSERT_EQ(id.getTestResult(),R"({"id":0})");
}

TEST(unit_test, set_server_test) {
    auto server = GameServer();
    auto* req = new RequestForServer();
    Response id = server.addUser(req);
    Response res = server.setNewPosition(req);
    ASSERT_EQ(res.getTestResult(),R"({"status": "ok"})");
}

TEST(unit_test, render_and_get_server_test) {
    auto server = GameServer();
    auto* req = new RequestForServer();
    Response id = server.addUser(req);
    Response res = server.setNewPosition(req);
    Response t = server.sendNewPosition(req);
    ASSERT_EQ(t.getTestResult(),R"([{"username":"test","x":"1","y":"1","rotation":"1","speed":1.000000,"stage":1,"isFinished":0}])");
}


int main(int argc, char **argv){
    ::testing::GTEST_FLAG(catch_exceptions) = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}