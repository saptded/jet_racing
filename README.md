### WebServer


## Depends
````
Boost: 1.65.1
c++-standart: 20
clang: 12
gcc: 11
````


## Use

```c++
import game_server;

int main(void){
    auto server = GameServer();
    server.start_server();
    return 0;
}
```