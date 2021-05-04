# WebServer


## Depends
````text
Boost: 1.76.0
c++ - standart: 20
clang: **not support**
gcc: 10
````


## Use server

```cpp
import game_server;

int main(void){
    auto server = GameServer();
    server.start();
    return 0;
}
```


## Use server

```cpp
#include <GameClient.hpp>;

int main(void){
    auto client = GameServer();
    client.send_data();
    return 0;
}
```