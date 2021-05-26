//
// Created by dark0ghost on 24.05.2021.
//

#ifndef JET_RACING_TRAITS_H
#define JET_RACING_TRAITS_H
#include <restinio/all.hpp>
/*
 * кастомные настройки сервера, не трогать их , если не ознакомлены с документацией
 */
struct ServerTraits : public restinio::default_traits_t{
    using request_handler_t [[maybe_unused]] = restinio::router::express_router_t<>;
};
#endif  // JET_RACING_TRAITS_H
