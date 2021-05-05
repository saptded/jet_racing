//
// Created by dark0ghost on 05.05.2021.
//

#ifndef LIBSERVER_INTERFACE_FOR_HIGH_LEVEL_API_H
#define LIBSERVER_INTERFACE_FOR_HIGH_LEVEL_API_H
#include <asio.hpp>

class asio_timer_manager_t;
class  null_logger_t;
class noop_strand_t;
class default_strand_t;


struct autodetect_request_handler_type;
template <
        typename Timer_Manager,
        typename Logger,
        typename Request_Handler = autodetect_request_handler_type,
        typename Strand = default_strand_t,
        typename Socket = asio::ip::tcp::socket >
struct traits_t;



template <
        typename Timer_Manager,
        typename Logger,
        typename Request_Handler = autodetect_request_handler_type >
using single_thread_traits_t =
traits_t<Timer_Manager, Logger, Request_Handler, noop_strand_t >;

using default_single_thread_traits_t = single_thread_traits_t<
        asio_timer_manager_t,
        null_logger_t >;

template<typename Traits = default_single_thread_traits_t >
class run_on_this_thread_settings_t;

template<typename Traits>
run_on_this_thread_settings_t<Traits>
on_this_thread();

typedef void(run)(run_on_this_thread_settings_t<> &&settings);

#endif //LIBSERVER_INTERFACE_FOR_HIGH_LEVEL_API_H
