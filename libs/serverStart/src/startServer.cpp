//
// Created by dark0ghost on 24.05.2021.
//
#include <startServer.h>
#include <traits.h>

std::unique_ptr<running_server_instance_t<http_server_t<ServerTraits>>> startServer(GameServer& server, ConnectionData& connectionData, std::size_t poolSize = 16){
    // маршртутизатор фреймоврка
    auto router = std::make_unique<restinio::router::express_router_t<>>();

    // устанавливает позицию по выданому ключу
    router->http_get(
        R"(/set_position)",
        [&server](auto req, auto params) {
            return (server.template setNewPosition(req)).done();
        }
    );
    /*
     * ожидает имя (id)
     * /add?username=1
     * возвращает уникальный id
     */
    router->http_get(
        R"(/add)",
        [&server](auto req, auto params) {
            return (server.template addUser(req)).done();
        }
    );

    /*
     * отправляет весь доступный буфер
     */
    router->http_get(
        R"(/get_updates)",
        [&server](auto req, auto params) {
            return (server.template sendNewPosition(req)).done();
        }
    );

    /*
     * для поиска сессий
     * возвращает json в котором сказано что запущен jst_racing
     */
    router->http_get(
        R"(/ping)",
        [&server](auto req, auto params) {
            return (server.template ping(req)).done();
        }
    );

    /*
     * если путь не найден
     */
    router->non_matched_request_handler(
        [](auto req){
            return req->create_response(restinio::status_not_found()).connection_close().done();
        });

    // https://stiffstream.com/en/docs/restinio/0.6/usingrestiniorun.html
    std::unique_ptr<running_server_instance_t<http_server_t<ServerTraits>>> serverRestinio = restinio::run_async<ServerTraits>(
            // Asio's io_context to be used.
            // HTTP-server will use own Asio's io_context object.
            restinio::own_io_context(),
            // The settings for the HTTP-server.
            restinio::server_settings_t<ServerTraits>{}.address("127.0.0.1").port(8080).request_handler(std::move(router)),
            //.request_handler(std::move(router)),
            // The size of thread-pool for the HTTP-server.
            poolSize);
    return serverRestinio;
}