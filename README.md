### WebServer


## Depends
````
Boost: 1.76.0
c++-standart: 20
clang: **not support**
gcc: 10
````


## Use

```c++
import game_server;

int main(void){
    auto server = GameServer();
    server.start();
    return 0;
}
```