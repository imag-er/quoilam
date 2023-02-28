#pragma once
#include <string>
#include <functional>
#include "rpc_msg_def.hpp"
namespace quoilam
{
    using Byte = char;

    class Server
    {
    public:
        Server();
        void listen(const std::string& ip, int port);
        void exec();

        void listen_callback(int socket_);

        ~Server();
    protected:
        const std::string LP(const std::string&);
        
        int listen_socket;
    };
};