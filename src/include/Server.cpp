#include <string>
#include <functional>
#include "Server.h"
#include <sys/fcntl.h>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <cstring>
#include <thread>
#include <chrono>
#include "Singleton.hpp"
#include "Typedef.h"
// 构造函数 初始化socket 线程池
quoilam::Server::Server(const Options& option):
    quoilam::SocketBase("server"),
    tpool(singleton<ThreadPool>::instance(16)),
    opt(option)
{

    owned_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (owned_socket < 0)
        handle_error("cannot create socket");
    logger->log("successfully listen port");

    // 检查线程池
    if (tpool == nullptr)
    {
        logger->log("thread pool initialization failed");
        return;
    }
    logger->log("thread pool successfully initialized");

}

void quoilam::Server::handle_quoilam_socket(int client_socket, sockaddr_in s_info)
{
    int flags = fcntl(client_socket, F_GETFL, 0);
    fcntl(client_socket, F_SETFL, flags & ~O_NONBLOCK);

    tpool->push_task(
        std::bind(&Server::listen_callback, this, std::placeholders::_1),
        client_socket);


}

// 监听端口
void quoilam::Server::listen(const std::string& ip, int port)
{
    struct sockaddr_in* server_addr = new sockaddr_in;
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr->sin_port = htons(port);

    // bind到端口
    int irtn = ::bind(owned_socket, (struct sockaddr*)server_addr, sizeof(*server_addr));
    if (irtn < 0)
    {
        handle_error("unable to bind ip");
        return;
    }

    logger->log("successfully binded");

    // 监听端口
    delete server_addr;
    irtn = ::listen(owned_socket, 64);
    if (irtn < 0)
    {
        handle_error("unable to listen");
        return;
    }
    logger->log("listening");



}

void quoilam::Server::exec()
{
    while (1)
    {
        struct sockaddr_in client_addr;
        int client_socket, socklen = sizeof(client_addr);

        if ((client_socket =
            accept(owned_socket,
                (struct sockaddr*)&client_addr,
                (socklen_t*)&socklen)) != -1)
        {

            logger->log("socket_id:", client_socket,
                "\tip: ", inet_ntoa(client_addr.sin_addr),
                "\tport: ", client_addr.sin_port,
                "\tcurrent threadpool size: ", tpool->running_size()
            );

            if (opt.custom)
                handle_custom(client_socket, client_addr);
            else
                handle_quoilam_socket(client_socket, client_addr);
        }
    }
}

quoilam::Server::~Server()
{
    close(owned_socket);
    tpool->~ThreadPool();

    auto it = client_sockets.begin();
    while (it != client_sockets.end())
    {
        close(*it);
        client_sockets.erase(it);
    }
}

void quoilam::Server::listen_callback(int socket_)
{
    logger->log("socket_id:", socket_, "\t thread started");
    uint32_t recvstr_len;
    using namespace std::chrono_literals;
    int iret = ::recv(socket_, &recvstr_len, 4, MSG_WAITALL);
    if (iret < 0)
    {
        logger->log("receiving lengthdata failed");
        return;
    }
    logger->log("got length data:", recvstr_len);

    Byte* buf = new Byte[recvstr_len];
    ::recv(socket_, buf, recvstr_len, MSG_WAITALL);
    logger->log("received:\t", buf);

    // 暂时这么做 假定收发长度相同 还有待改进
    uint32_t sendstr_len = recvstr_len;
    // Byte *response_buffer = new Byte[recvstr_len]{0};

    // byte_explain(buf, response_buffer, recvstr_len);
    logger->log("processed message[20:]:", buf + 20);
    ::send(socket_, &sendstr_len, 4, 0);
    ::send(socket_, buf, sendstr_len, 0);

    delete[] buf;
}
