#pragma once 
#include "rpc_msg_def.hpp"
#include <string>
class Client
{
public:
    void connect(const std::string& ip, int port);
    Response* orgcall(Request* request);

    template<class T>
    const T& call(Request* request);
};

template<class T>
const T& Client::call<T>(Request* request)
{
    return *(T*)orgcall(request);
}
