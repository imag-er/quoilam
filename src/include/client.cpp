#include "client.h"
#include "singleton.hpp"
#include "socket_base.h"

quoilam::Client::Client():
    socket_base("client")
{


}
void quoilam::Client::connect(const std::string& ip, int port)

{
    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    // 创建socket
    owned_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (owned_socket == -1)
    {
        logger->log("unable to create socket\terrno:", errno);
        return;
    }
    logger->log("created socket");


    // 把socket设置为阻塞模式
    int flags = fcntl(owned_socket, F_GETFL, 0);
    fcntl(owned_socket, F_SETFL, flags & ~O_NONBLOCK);

    // 连接服务器
    int iret = ::connect(owned_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (iret == -1)
    {
        logger->log("unable to connect server\terrno:", errno);
        return;
    }
    logger->log("server connected");
}

const std::string quoilam::Client::send(const std::string& str)
{
    logger->log("sending msg:", str);
    send_size(str.length());
    send_bytes((char32_t*)&str, str.length());
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
    int irtn = ::send(owned_socket, &size, 4, 0);

    logger->log("told server msg_size:", size, "  bytes");
}
void quoilam::Client::send_bytes(const quoilam::Byte* data, const uint32_t& nbytes)
{
    // 发送request
    int irtn = ::send(owned_socket, data, nbytes, 0);
    logger->log(irtn, "bytes of data sent");
}
const uint32_t quoilam::Client::recv_size()
{
    // 接收从服务器发来的response长度
    uint32_t recvstr_len;
    int irtn = ::recv(owned_socket, &recvstr_len, 4, MSG_WAITALL);
    logger->log(recvstr_len, " bytes to receive");
    return recvstr_len;
}
void quoilam::Client::recv_bytes(Byte* buffer, const uint32_t& nbytes)
{
    // 接受response
    Byte* recv_buf = new Byte[nbytes];
    int irtn = ::recv(owned_socket, recv_buf, nbytes, MSG_WAITALL);
    logger->log("received", recv_buf);
    memcpy(buffer, recv_buf, nbytes);
    delete[] recv_buf;
    return;
}

quoilam::Client::~Client()
{
    close(owned_socket);
}