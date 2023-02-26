#pragma once
#include <string>
#include <functional>
#include "rpc_msg_def.hpp"
namespace quoilam
{
    class Server
    {
    public:
        Server();
        void listen(const std::string& ip, int port);
        void bind(const std::string&, std::function<Response* (Request*)> handler);
        void exec();

    private:
        int listen_socket;
    };
};