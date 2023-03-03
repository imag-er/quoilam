#include <string>
#include <functional>
#include "server.h"
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <memory>
#include <cstring>
#include <thread>
#include <chrono>
quoilam::Server::Server() : listen_socket(socket(AF_INET, SOCK_STREAM, 0))
{

    if (listen_socket < 0)
    {
        std::cout << "server:unable to create socket" << std::endl;
    }
    std::cout << "server:listen socket" << std::endl;
}
void quoilam::Server::listen(const std::string &ip, int port)
{
    struct sockaddr_in *server_addr = new sockaddr_in;
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr->sin_port = htons(port);

    int irtn = ::bind(listen_socket, (struct sockaddr *)server_addr, sizeof(*server_addr));
    if (irtn < 0)
    {
        std::cout << "server:unable to bind" << std::endl;
        return;
    }
    std::cout << "server: bind " << std::endl;

    delete server_addr;
    irtn = ::listen(listen_socket, 10);
    if (irtn < 0)
    {
        std::cout << "server:unable to listen" << std::endl;
        return;
    }
    std::cout << "server:listen " << std::endl;

    // return == -1
}

void quoilam::Server::exec()
{

    while (1)
    {
        struct sockaddr_in client_addr;
        int client_socket, socklen = sizeof(client_addr);

        if ((client_socket =
                 accept(listen_socket,
                        (struct sockaddr *)&client_addr,
                        (socklen_t *)&socklen)) != -1)
        {
            // std::cout << "server:successfully connected client : " << inet_ntoa(client_addr.sin_addr) << std::endl;
            int flags = fcntl(client_socket, F_GETFL, 0);
            fcntl(client_socket, F_SETFL, flags & ~O_NONBLOCK);

            std::thread(
                std::bind(&Server::listen_callback, this, std::placeholders::_1),
                client_socket)
                .detach();
            std::cout << "socket id:" << client_socket << " connected" << std::endl;
            while (1)
            {
            }
        }
    }
}

quoilam::Server::~Server()
{
    close(listen_socket);
}

void quoilam::Server::byte_explain(const Byte *input, Byte *output, const int &input_len)
{
    memset(output, 0, input_len);
    memcpy(output, input, input_len);
    *output = input_len;
}

void quoilam::Server::listen_callback(int socket_)
{
    std::cout << "socket id:" << socket_ << " thread started" << std::endl;
    uint32_t recvstr_len;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
    int iret = ::recv(socket_, &recvstr_len, 4, MSG_WAITALL);
    if (iret <= 0)
    {
        std::cout << "server:receive error:" << iret << "\terrno:" << errno << std::endl;
    }
    std::cout << "server:" << recvstr_len << " bytes to be received" << std::endl;

    Byte *buf = new Byte[recvstr_len];
    ::recv(socket_, buf, recvstr_len, MSG_WAITALL);
    std::cout << "server:received:" << buf << std::endl;

    // 暂时这么做 假定收发长度相同 还有待改进
    uint32_t sendstr_len = recvstr_len;
    // Byte *response_buffer = new Byte[recvstr_len]{0};

    // byte_explain(buf, response_buffer, recvstr_len);
    std::cout << "server:explained message:" << buf << std::endl;
    ::send(socket_, &sendstr_len, 4, 0);
    ::send(socket_, buf, sendstr_len, 0);

    delete[] buf;
}
