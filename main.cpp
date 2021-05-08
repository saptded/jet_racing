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
            R"(/data/meter/)",
            [&server](auto req, auto params) {
                const auto qp = restinio::parse_query(req->header().query());

                return (server.template ping(req));
            }
    );




    restinio::run(
            restinio::on_this_thread<my_server_traits>()
                    .address("localhost")
                    .port(2021)
                    .request_handler(std::move(router)));

    return 0;
}
