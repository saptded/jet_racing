//
// Created by dark0ghost on 14.04.2021.
//
#include <gtest/gtest.h>
#define test_jet_racing
#include "GameClient.hpp"
#include "serialization.h"
#include <GameServer.hpp>
#include <string>

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

class RequestForServer{
public:
    Response create_response(){
        return Response();
    }
};

class request{

    template<class name>
    static Response getRequest(name t){
        return Response();
     }
};

TEST(stress_test, tests_input) {
    auto client = GameClient<request>();
    std::vector<Position> ret  = client.getUpdates<Response>();
    ASSERT_EQ(ret[0].username, "200");
}

TEST(serialization_test, tests_input) {
    Position user = Position{"racer", "1", "2", "4"};
    std::string response = writeToJson(user);
    ASSERT_EQ(response, "{\"username\":\"racer\",\"x\":1,\"y\":2,\"z\":4}");
}

TEST(unit_test,ping_server_test) {
    auto server = GameServer();
    auto* req = new RequestForServer();
    Response result = server.ping(req);
    ASSERT_EQ(result.getTestResult(), "{\"name\":\"jet_racing\"}");
}


int main(int argc, char **argv){
    ::testing::GTEST_FLAG(catch_exceptions) = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}