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
        void disconnect();

        const std::string send(const std::string& str);

        bool send_size(const uint32_t& size);
        bool send_bytes(const quoilam::Byte* data, const uint32_t& nbytes);
        const uint32_t recv_size();
        bool recv_bytes(Byte* buffer, const uint32_t& nbytes);
        ~Client();

    };

};
