#include "client.h"
#include <iostream>
#include <string>
#include <functional>
#include "rpc_msg_def.hpp"
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>


void quoilam::Client::connect(const std::string& ip, int port)
{
    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());


    connect_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (connect_socket == -1)
    {
        std::cout << "client:unable to create socket" << std::endl;
        return;
    }
    std::cout << "client:connect socket:" << std::endl;

    int iret = ::connect(connect_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (iret == -1)
    {
        std::cout << "client:unable to connect server" << iret << std::endl;
        return;
    }
    std::cout << "client:server connected" << std::endl;

}

quoilam::Response::Ptr quoilam::Client::orgcall(Request::Ptr request)
{
    const char* buffer = "test";
    int nbytessend = send(connect_socket, buffer, 4, 0);
    if (nbytessend < 0)
    {
        std::cout << "client:unable to send" << std::endl;
        return nullptr;
    }
    return nullptr;
}



quoilam::Client::~Client()
{
    close(connect_socket);

}