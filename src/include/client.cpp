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
    // TODO: 此处可以优化局部变量 共用内存 避免反复开辟
    uint32_t sendstr_len = str.length();

    // 先发送4字节的request长度数据
    int irtn = ::send(connect_socket, &sendstr_len, 4, 0);
    std::cout << "client:" << irtn << " bytes to be send" << std::endl;

    // 发送request
    irtn = ::send(connect_socket, str.c_str(), sendstr_len, 0);
    std::cout << "client:" << irtn << " bytes sent" << std::endl;

    // 接收从服务器发来的response长度
    uint32_t recvstr_len;
    irtn = ::recv(connect_socket, &recvstr_len, 4, MSG_WAITALL);
    std::cout << "client:" << irtn << " bytes to be receive" << std::endl;

    // 接受response
    Byte* recv_buf = new Byte[recvstr_len];
    irtn = ::recv(connect_socket, recv_buf, recvstr_len, MSG_WAITALL);
    std::cout << "client:received " << irtn << std::endl;


    const std::string rtn(recv_buf);
    delete[] recv_buf;
    return rtn;
}

quoilam::Client::~Client()
{
    close(connect_socket);
}