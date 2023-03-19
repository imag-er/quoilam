#pragma once
#include "StdLogger.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace quoilam
{
    class SocketBase
    {
    public:
        SocketBase(const std::string &name);

    protected:
        int owned_socket;
        const std::string name;

        StdLogger::SharedPtr logger;

        void handle_error(const std::string &msg);

    private:
    };

    using Byte = char;
    using Uint = uint32_t;

}
