#include "GameServer.cpp"


int main() {
    auto connection = Connection{8089};//, "localhost"};
    GameServer server(connection);
}

