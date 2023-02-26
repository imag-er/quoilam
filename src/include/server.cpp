#include <string>
#include <functional>
#include "rpc_msg_def.hpp"
#include "server.h"
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
quoilam::Server::Server()
{
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    // listen_socket == -1
}
void quoilam::Server::listen(const std::string& ip, int port)
{

}

void quoilam::Server::bind(const std::string&, std::function<Response* (Request*)> handler)
{

}


void quoilam::Server::exec()
{

}