#include <string>
#include <functional>
#include "server.h"
#include <sys/fcntl.h>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <cstring>
#include <thread>
#include <chrono>
#include "singleton.hpp"

// 构造函数 初始化socket 线程池
quoilam::Server::Server() : listen_socket(socket(AF_INET, SOCK_STREAM, 0)),
                            tpool(singleton<ThreadPool>::instance(16))
{
    // 检查监听socket
    if (listen_socket < 0)
    {
        std::cout << "server:unable to create socket" << std::endl;
        return;
    }
    std::cout << "server:listen socket" << std::endl;

    // 检查线程池
    if (tpool != nullptr)
    {
        std::cout << "server:thread pool initialized successfully" << std::endl;
        return;
    }
    std::cout << "server:threadpool started successfully" << std::endl;
}

void quoilam::Server::handle_socket(int client_socket, sockaddr_in s_info)
{
    int flags = fcntl(client_socket, F_GETFL, 0);
    fcntl(client_socket, F_SETFL, flags & ~O_NONBLOCK);

    tpool->push_task(
        std::bind(&Server::listen_callback, this, std::placeholders::_1),
        client_socket);

    std::cout << "socket id:" << client_socket << "\t"
              << "ip:" << inet_ntoa(s_info.sin_addr) << std::endl;
}

// 监听端口
void quoilam::Server::listen(const std::string &ip, int port)
{
    struct sockaddr_in *server_addr = new sockaddr_in;
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr->sin_port = htons(port);

    // bind到端口
    int irtn = ::bind(listen_socket, (struct sockaddr *)server_addr, sizeof(*server_addr));
    if (irtn < 0)
    {
        std::cout << "server:unable to bind:" <<irtn<<  std::endl;
        return;
    }
    std::cout << "server: bind " << std::endl;

    // 监听端口
    delete server_addr;
    irtn = ::listen(listen_socket, 10);
    if (irtn < 0)
    {
        std::cout << "server:unable to listen" << std::endl;
        return;
    }
    std::cout << "server:listen " << std::endl;
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
            handle_socket(client_socket, client_addr);
        }
    }
}

quoilam::Server::~Server()
{
    close(listen_socket);
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
