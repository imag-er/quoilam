#pragma once
#include <string>
#include "StdLogger.h"
#include "SocketBase.h"
namespace quoilam
{
    class Client: protected SocketBase
    {
    public:
        Client();
        void connect(const std::string& ip, int port);
        void disconnect();

        const std::string send(const std::string& str);

        bool send_size(const Uint& size);
        bool send_bytes(const quoilam::Byte* data, const Uint& nbytes);
        const Uint recv_size();
        bool recv_bytes(Byte* buffer, const Uint& nbytes);
        ~Client();

    };

};
