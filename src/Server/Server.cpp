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
namespace quoilam::network
{
    using namespace quoilam;
#ifndef _WIN32
    // 构造函数 初始化socket 线程池
    Server::Server(const Options &option)
        : SocketBase("server"),
          tpool(util::singleton<util::ThreadPool>::instance(16)),
          opt(option)
    {
        // 初始化socket
        owned_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (owned_socket < 0)
        {
            handle_error("cannot create socket");
            close(owned_socket);
            return;
        }
        logger->log("successfully listen port");

        // 设置端口复用
        if (opt.reuse_port)
        {
            int optval = 1;
            int res = setsockopt(owned_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
            if (res < 0)
            {
                handle_error("unable to set port reuse");
                close(owned_socket);
                return;
            }
        }

        // 检查线程池
        if (tpool == nullptr)
        {
            logger->log("thread pool initialization failed");
            close(owned_socket);
            return;
        }
        logger->log("thread pool successfully initialized");
    }

    void Server::handle_quoilam_socket(int client_socket, sockaddr_in s_info)
    {
        // 设置阻塞
        int flags = fcntl(client_socket, F_GETFL, 0);
        fcntl(client_socket, F_SETFL, flags & ~O_NONBLOCK);

        tpool->push_task(
            std::bind(&Server::quoilam_callback, this, std::placeholders::_1),
            client_socket);
    }

    void Server::handle_default_socket(int client_socket, sockaddr_in s_info)
    {
        tpool->push_task(
            std::bind(&Server::default_callback, this, std::placeholders::_1),
            client_socket);
    }

    // 监听端口
    void Server::listen(const std::string &ip, int port)
    {
        struct sockaddr_in *server_addr = new sockaddr_in;
        server_addr->sin_family = AF_INET;
        server_addr->sin_addr.s_addr = inet_addr(ip.c_str());
        server_addr->sin_port = htons(port);

        // bind到端口
        int irtn = ::bind(owned_socket, (struct sockaddr *)server_addr, sizeof(*server_addr));
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

    void Server::exec()
    {
        while (1)
        {
            struct sockaddr_in client_addr;
            int client_socket, socklen = sizeof(client_addr);

            if ((client_socket =
                     accept(owned_socket,
                            (struct sockaddr *)&client_addr,
                            (socklen_t *)&socklen)) != -1)
            {

                logger->log("socket_id:", client_socket,
                            "\tip: ", inet_ntoa(client_addr.sin_addr),
                            "\tport: ", client_addr.sin_port,
                            "\tcurrent threadpool size: ", tpool->running_size());

                if (opt.protocol == Options::ProtoType::custom)
                    handle_custom(client_socket, client_addr);
                else if (opt.protocol == Options::ProtoType::quoilam_socket)
                    handle_quoilam_socket(client_socket, client_addr);
            }
        }
    }

    Server::~Server()
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

    void Server::quoilam_callback(int socket_)
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

        Byte *buf = new Byte[recvstr_len];
        ::recv(socket_, buf, recvstr_len, MSG_WAITALL);
        logger->log("received:\t", buf);

        // 暂时这么做 假定收发长度相同 还有待改进
        uint32_t sendstr_len = recvstr_len;
        // Byte *response_buffer = new Byte[recvstr_len]{0};

        // byte_explain(buf, response_buffer, recvstr_len);
        logger->log("processed message:", buf);
        ::send(socket_, &sendstr_len, 4, 0);
        ::send(socket_, buf, sendstr_len, 0);

        delete[] buf;

        close(socket_);
    }
    void Server::default_callback(int socket_)
    {
        logger->log("socket_id:", socket_, "\t thread started");

        Byte *buf = new Byte[2048];
        ::recv(socket_, buf, 2048, 0);
        logger->log("received:\t", buf);

        logger->log("processed message:", buf);
        ::send(socket_, buf, strlen(buf), 0);

        delete[] buf;

        close(socket_);
    }
#endif
}
