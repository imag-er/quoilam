#include <string>
#include <functional>
#include "rpc_msg_def.hpp"
#include "server.h"
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
quoilam::Server::Server()
{
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    // listen_socket == -1



}
void quoilam::Server::listen(const std::string& ip, int port)
{
    struct sockaddr_in* server_addr = new sockaddr_in;
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr->sin_port = htons(port);

    ::bind(listen_socket, (struct sockaddr*)server_addr, sizeof(*server_addr));
    // return == -1

    delete server_addr;
    ::listen(listen_socket, 10);
    // return == -1

}

void quoilam::Server::bind(const std::string& service_name, std::function<Response* (Request*)> handler)
{

}


void quoilam::Server::exec()
{

    while (1)
    {
        struct sockaddr_in client_addr;
        int client_socket, socklen = sizeof(client_addr);

        if (client_socket =
            accept(listen_socket,
                (struct sockaddr*)&client_addr,
                (socklen_t*)&socklen) != -1)
        {
            std::cout << "successfully connected" << inet_ntoa(client_addr.sin_addr) << std::endl;
            while (1) {}
        }
    }
}