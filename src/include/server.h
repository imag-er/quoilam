#pragma once
#include <string>
#include <functional>
#include "rpc_msg_def.hpp"
class Server
{
public:
    void listen(const std::string& ip, int port);
    void bind(const std::string&, std::function<Response* (Request*)> handler);
    void exec();
};