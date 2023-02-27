#pragma once 
#include "rpc_msg_def.hpp"
#include <string>
namespace quoilam
{
    class Client
    {
    public:
        void connect(const std::string& ip, int port);
        const Response orgcall(const Request& request);

        template<class RequestType, class ResponseType>
        const ResponseType call(const RequestType& request);

        ~Client();
    protected:
        int connect_socket;
    };


    template<class RequestType, class ResponseType>
    const ResponseType Client::call(const RequestType& request)
    {
        return dynamic_cast<const ResponseType*>(&this->orgcall(
            dynamic_cast<const Request&>(request)
        ));
    }

};
