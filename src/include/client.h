#pragma once 
#include "rpc_msg_def.hpp"
#include <string>
namespace quoilam
{
    class Client
    {
    public:
        void connect(const std::string& ip, int port);

        

        ~Client();
    protected:
        int connect_socket;
    };



};
