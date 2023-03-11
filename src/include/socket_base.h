#pragma once
#include <string>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "stdlogger.h"
#include <memory>

namespace quoilam
{
    class socket_base
    {
    public:
        socket_base(const std::string& name);

    protected:
        int owned_socket;
        const std::string name;

        StdLogger::SharedPtr logger;

        void handle_error(const std::string& msg);

    private:
    };

    using Byte = char32_t;

}
