#pragma once
#include <string>
#include <functional>
#include <sys/socket.h>
#include "threadpool.h"
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "stdlog.h"
namespace quoilam
{
    using Byte = char;

    class Server
    {
    public:
        Server();
        void listen(const std::string& ip, int port);
        void exec();


        ~Server();
    protected:
        void handle_socket(int client_socket, sockaddr_in s_info);
        void listen_callback(int socket_);

    private:
        ThreadPool* tpool = nullptr;
        int listen_socket;
        stdlog* logger = nullptr;
    };
};