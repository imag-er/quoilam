#pragma once
#include <string>
#include "StdLogger.h"
#include "SocketBase.h"
namespace quoilam::network
{
    class Client: protected SocketBase
    {
    public:
        Client();
        void connect(const std::string& ip, int port);
        void disconnect();

        const std::string send(const std::string& str);

        bool send_size(const UInt& size);
        bool send_bytes(const quoilam::Byte* data, const UInt& nbytes);
        const UInt recv_size();
        bool recv_bytes(Byte* buffer, const UInt& nbytes);
        ~Client();

    };

};
