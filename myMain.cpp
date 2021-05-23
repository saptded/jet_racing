#include "presenter.hpp"
#include "MathCalculation.h"
#include <serialization.h>
#include <restinio/all.hpp>




int main() {
//    float radian = findCosine(-850, -850.007629, -9200, -9199.18262);
//
//    std::cout << radian;


    int id = 0;

    Presenter *presenter = Presenter::create(id);
   // presenter->run();
    restinio::run(
            restinio::on_this_thread()
                    .port(2198)
                    .address("localhost")
                    .request_handler([](auto req) {
                        return req->create_response().set_body("Hello, World!").done();
                    }));

    delete presenter;
}