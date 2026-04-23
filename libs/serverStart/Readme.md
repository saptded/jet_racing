# Запуск сервера

## traits.h
Задаёт настройки сервера. ***НЕ РЕКОМЕНДУЕТСЯ ТРОГАТЬ, ЕСЛИ НЕ ЧИТАЛИ ДОКУМЕНТАЦИЮ***

## startServer.h
отвечает за инициализацию сервера на тред пуллах

```cpp
void start_server(){
    gameServer = GameServer();
    ConnectionData connectionData = {2021, "localhost"}; // сетевые данные на которых запуститься сервер
    server = startServer(gameServer, connectionData);
    
    server->stop(); // очищение http-server
    gameServer.close(); // очистка игрового сервера. не путать с low level http server
}
```