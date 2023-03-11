#pragma once
#include <string>
#include <functional>
#include <sys/socket.h>
#include "threadpool.h"
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "stdlogger.h"
#include "socket_base.h"
namespace quoilam
{

    class Server: protected socket_base
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
        std::shared_ptr<ThreadPool> tpool ;
    };
};