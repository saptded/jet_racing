# WebServer
[![GitHub Super-Linter](https://github.com/saptded/jet_racing/workflows/Lint%20Code%20Base/badge.svg)](https://github.com/marketplace/actions/super-linter)

## Depends
````text
c++ - standart: 17
clang: **not support**
gcc: 10
````

## Use server

```cpp
#include <GameServer.hpp>

int main(void){
  auto server = GameServer();
  router->http_get(R"(/register))",[&server](auto param){ return server.addUser(param)});

  CustomHttpServer::run(router)
return 0;
}
```

## Use server with restinio

```cpp
#include <restinio/all.hpp>
using namespace restinio;
#include <GameServer.hpp>

template<typename T>
std::ostream & operator<<(std::ostream & to, const restinio::optional_t<T> & v) {
    if(v) to << *v;
    return to;
}

struct my_server_traits : public restinio::default_single_thread_traits_t {
    using request_handler_t = restinio::router::express_router_t<>;
};

int main() {
    auto server = GameServer();
    auto router = std::make_unique<restinio::router::express_router_t<>>();
    router->http_get(
            R"(/data)",
            [&server](auto req, auto params) {
                std::cout<< 2;
                return (server.template setNewPosition(req));
            }
    );
    router->http_get(
            R"(/add)",
            [&server](auto req, auto params) {
                return (server.template addUser(req));
            }
    );
    router->http_get(
            R"(/update)",
            [&server](auto req, auto params) {
                return (server.template sendNewPosition(req));
            }
    );
    restinio::run(
            restinio::on_this_thread<my_server_traits>()
                    .address("localhost")
                    .port(2021)
                    .request_handler(std::move(router)));
    
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
    client.sendData(<data: Position>);
    
    return 0;
}
```