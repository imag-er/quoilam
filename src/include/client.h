#pragma once 
#include "rpc_msg_def.hpp"
#include <string>
namespace quoilam
{
    class Client
    {
    public:
        void connect(const std::string& ip, int port);
        Response* orgcall(Request* request);

        template<class RequestType>
        Response::Ptr call(RequestType* request);
    };


    template<class RequestType>
    Response::Ptr Client::call(RequestType* request)
    {
        return *this->orgcall(
            dynamic_cast<Request*>(request)
        );
    }

};
