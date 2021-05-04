//
// Created by dark0ghost on 15.04.2021.
//
#include "AbstractClient.hpp"
#include "../hpp/ServerDataConnection.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>


class GameClient: public AbstractClient{
    boost::asio::ip::tcp::endpoint ep;
    boost::asio::ip::tcp::socket sock;
    boost::asio::streambuf request;
    boost::asio::streambuf response;

    ServerDataConnection back_up_server_data_connection;

     void handle_resolve(const boost::system::error_code& err,
                               boost::asio::ip::tcp::resolver::iterator endpoint_iterator){
        if (!err)
        {
            // Attempt a connection to the first endpoint in the list. Each endpoint
            // will be tried until we successfully establish a connection.
            boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
            sock.async_connect(endpoint,
                                  boost::bind(&client::handle_connect, this,
                                              boost::asio::placeholders::error, ++endpoint_iterator));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

   void handle_connect(const boost::system::error_code& err,
                       const boost::asio::ip::tcp::resolver::iterator& endpoint_iterator)
    {
        if (!err)
        {
            // The connection was successful. Send the request.
            boost::asio::async_write(sock, request,
                                     boost::bind(&client::handle_write_request, this,
                                                 boost::asio::placeholders::error));
        }
        else if (endpoint_iterator !=  boost::asio::ip::tcp::resolver::iterator())
        {
            // The connection failed. Try the next endpoint in the list.
            sock.close();
            boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
            sock.async_connect(endpoint,
                                  boost::bind(&client::handle_connect, this,
                                              boost::asio::placeholders::error, ++endpoint_iterator));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_write_request(const boost::system::error_code& err){
        if (!err)
        {
            // Read the response status line. The response_ streambuf will
            // automatically grow to accommodate the entire line. The growth may be
            // limited by passing a maximum size to the streambuf constructor.
            boost::asio::async_read_until(sock, response, "\r\n",
                                          boost::bind(&GameClient::handle_read_status_line, this,
                                                      boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_read_status_line(const boost::system::error_code& err)
    {
        if (!err)
        {
            // Check that response is OK.
            std::istream response_stream(&response);
            std::string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline(response_stream, status_message);
            if (!response_stream || http_version.substr(0, 5) != "HTTP/")
            {
                std::cout << "Invalid response\n";
                return;
            }
            if (status_code != 200)
            {
                std::cout << "Response returned with status code ";
                std::cout << status_code << "\n";
                return;
            }

            // Read the response headers, which are terminated by a blank line.
            boost::asio::async_read_until(sock, response, "\r\n\r\n",
                                          boost::bind(&GameClient::handle_read_headers, this,
                                                      boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err << "\n";
        }
    }

    void handle_read_headers(const boost::system::error_code& err)
    {
        if (!err)
        {
            // Process the response headers.
            std::istream response_stream(&response);
            std::string header;
            while (std::getline(response_stream, header) && header != "\r")
                std::cout << header << "\n";
            std::cout << "\n";

            // Write whatever content we already have to output.
            if (response.size() > 0)
                std::cout << &response;

            // Start reading remaining data until EOF.
            boost::asio::async_read(socket, response,
                                    boost::asio::transfer_at_least(1),
                                    boost::bind(&GameClient::handle_read_content, this,
                                                boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err << "\n";
        }
    }

    void handle_read_content(const boost::system::error_code& err) {
        if (!err) {
            // Write all of the data that has been read so far.
            std::cout << &response;

            // Continue reading remaining data until EOF.
            boost::asio::async_read(sock, response,
                                    boost::asio::transfer_at_least(1),
                                    boost::bind(&GameClient::handle_read_content, this,
                                                boost::asio::placeholders::error));
        } else if (err != boost::asio::error::eof) {
            std::cout << "Error: " << err << "\n";
        }
    }

    std::string get_request(){
        return "";
    }

public:
    explicit GameClient(ServerDataConnection server_data_connection, boost::asio::io_service& io_service): sock(io_service){
        back_up_server_data_connection = server_data_connection;
        ep = boost::asio::ip::tcp::endpoint (boost::asio::ip::address::from_string( back_up_server_data_connection.ip),  back_up_server_data_connection.port);
    }

   void close() override{

   }
   void send_data(DataGame data) override{

   }
   std::string get_data() {

       return std::string();
   }

    DataGame get_updates(){

        return DataGame();
    }


};

