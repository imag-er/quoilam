#include "client.h"
#include <iostream>
#include <string>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>

void quoilam::Client::connect(const std::string& ip, int port)
{
    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    // 创建socket
    connect_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (connect_socket == -1)
    {
        std::cout << "client:unable to create socket" << std::endl;
        return;
    }
    std::cout << "client:create socket" << std::endl;

    // 把socket设置为阻塞模式
    int flags = fcntl(connect_socket, F_GETFL, 0);
    fcntl(connect_socket, F_SETFL, flags & ~O_NONBLOCK);

    // 连接服务器
    int iret = ::connect(connect_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (iret == -1)
    {
        std::cout << "client:unable to connect server" << iret << std::endl;
        return;
    }
    std::cout << "client:server connected" << std::endl;
}

const std::string quoilam::Client::send(const std::string& str)
{
    send_size(str.length());
    send_bytes((char*)&str, str.length());
    int nbytes = recv_size();
    Byte* buffer = new Byte[nbytes]{ 0 };
    recv_bytes(buffer, nbytes);
    std::string recvstr = *(std::string*)buffer;
    delete[] buffer;
    return recvstr;
}

void quoilam::Client::send_size(const uint32_t& size)
{
    // 先发送4字节的request长度数据
    int irtn = ::send(connect_socket, &size, 4, 0);
    std::cout << "client:\t" << irtn << " bytes to be send" << std::endl;
}
void quoilam::Client::send_bytes(const quoilam::Byte* data, const uint32_t& nbytes)
{
    // 发送request
    int irtn = ::send(connect_socket, data, nbytes, 0);
    std::cout << "client:\t" << irtn << " bytes sent" << std::endl;
}
const uint32_t quoilam::Client::recv_size()
{
    // 接收从服务器发来的response长度
    uint32_t recvstr_len;
    int irtn = ::recv(connect_socket, &recvstr_len, 4, MSG_WAITALL);
    std::cout << "client:\t" << irtn << " bytes to be receive" << std::endl;
    return recvstr_len;
}
void quoilam::Client::recv_bytes(Byte* buffer, const uint32_t& nbytes)
{
    // 接受response
    Byte* recv_buf = new Byte[nbytes];
    int irtn = ::recv(connect_socket, recv_buf, nbytes, MSG_WAITALL);
    std::cout << "client:received:\t" << irtn << std::endl;
    memcpy(buffer, recv_buf, nbytes);
    delete[] recv_buf;
    return;
}

quoilam::Client::~Client()
{
    close(connect_socket);
}