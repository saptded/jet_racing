//
// Created by dark0ghost on 05.04.2021.
//


#include  <cstdlib>
#ifndef LIBSERVER_ABSTRACTSERVER_HPP
#define LIBSERVER_ABSTRACTSERVER_HPP


class AbstractServer{
public:

    virtual void start_server() = 0;
    virtual void close() = 0;
    virtual void update_data_from_user() = 0;
protected:
    size_t port = 0;

};
#endif //LIBSERVER_ABSTRACTSERVER_HPP
