#pragma once 
#include "rpc_msg_def.hpp"
#include <string>
namespace quoilam
{
    class Client
    {
    public:
        void connect(const std::string& ip, int port);
        Response::Ptr orgcall(Request::Ptr request);

        template<class RequestType, class ResponseType>
        ResponseType* call(RequestType* request);

        ~Client();
    protected:
        int connect_socket;
    };


    template<class RequestType, class ResponseType>
    ResponseType* Client::call(RequestType* request)
    {
        return dynamic_cast<ResponseType*>(this->orgcall(
            dynamic_cast<Request::Ptr>(request)
        ));
    }

};
