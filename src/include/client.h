#pragma once
#include <string>
#include "stdlog.h"
namespace quoilam
{
    using Byte = char;
    class Client
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

    protected:
        int connect_socket;
        stdlog* logger = nullptr;

    };

};
