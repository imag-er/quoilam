#include "HttpServer.h"

namespace quoilam::network
{
#ifndef _WIN32
    HttpServer::HttpServer(std::string ip, UInt port)
        : Server(Options(Options::ProtoType::custom,true))
    {
        Server::listen(ip, port);
    }

    void HttpServer::handle_custom(
        int client_socket,
        sockaddr_in s_info)
    {
        tpool->push_task(
            std::bind(&HttpServer::http_response_callback, this, std::placeholders::_1),
            client_socket);
    }

    void HttpServer::http_response_callback(int client_socket)
    {
        // 每次刷新都是建立新连接
        UInt buf_size = 2048;
        logger->log("handled");
        char *buffer = new char[buf_size]{0};
        while (1)
        {
            ssize_t count = recv(client_socket, buffer, buf_size, 0);
            if (count > 0)
            {
                std::cout << buffer << "\n-----------------------" << std::endl;
                std::string resp = process(buffer);
                send(client_socket, resp.c_str(), resp.size(), 0);
                break;
            }
        }
        close(client_socket);
    }
#endif
}