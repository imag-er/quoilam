#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

#include "StdLogger.h"
#include "Typedef.h"

#ifndef WIN32
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif
namespace quoilam::network
{
    using namespace quoilam;
    class SocketBase
    {
    public:
        SocketBase(const std::string &name);

    protected:
        int owned_socket;
        const std::string name;

        io::StdLogger::SharedPtr logger;

        void handle_error(const std::string &msg);

    private:
    };

}
