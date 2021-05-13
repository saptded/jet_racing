//
// Created by dark0ghost on 06.05.2021.
//

#ifndef LIBSERVER_CURL_INTARFACE_H
#define LIBSERVER_CURL_INTARFACE_H
class Response;

template <typename... Ts>
Response Get(Ts&&... ts);

class Url;

class Parameters;


#endif //LIBSERVER_CURL_INTARFACE_H
