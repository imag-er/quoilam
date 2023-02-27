#include "client.h"
#include <iostream>
#include <string>
#include <functional>
#include "rpc_msg_def.hpp"
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>


void quoilam::Client::connect(const std::string& ip, int port)
{

}

quoilam::Response* quoilam::Client::orgcall(Request* request)
{

}