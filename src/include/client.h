#pragma once
#include <string>
#include "stdlogger.h"
#include "socket_base.h"
namespace quoilam
{

    class Client: protected socket_base
    {
    public:
        Client();
        void connect(const std::string& ip, int port);

        const std::string send(const std::string& str);

        void send_size(const uint32_t& size);
        void send_bytes(const quoilam::Byte* data, const uint32_t& nbytes);
        const uint32_t recv_size();
        void recv_bytes(Byte* buffer, const uint32_t& nbytes);
        ~Client();



    };

};
