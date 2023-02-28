#pragma once 
#include "rpc_msg_def.hpp"
#include <string>
namespace quoilam
{
    using Byte = char;
    class Client
    {
    public:
        void connect(const std::string& ip, int port);

        const std::string send(const std::string& str);

        ~Client();
    protected:
        int connect_socket;
    };



};
