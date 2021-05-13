# WebServer


## Depends
````text
Boost: 1.76.0
c++ - standard: 20
clang: **not support**
gcc: 10
````


## Use server

```cpp
#include <GameServer.hpp>

int main(void){
  auto router = std::make_unique<router::express_router_t<>>();
  auto server = GameServer();
  router->http_get(R"(/register))",server.addUser);

  
  restinio::run(
    restinio::on_this_thread()
               .port(8081)
               .address("localhost")
               .request_handler(router)
               );
return 0;
}
```


## Use client

```cpp
#include <cpr/cpr.h>
using namespace cpr;
#include <GameClient.hpp>


int main(void){
    Connection conn = {"localhost", "9873"};
    auto client = GameClient(conn, Get);
    client.sendData();
    return 0;
}
```