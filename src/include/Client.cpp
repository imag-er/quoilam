#include "Client.h"
#include "Singleton.hpp"
#include "SocketBase.h"

namespace quoilam
{

    Client::Client():
        SocketBase("client")
    {


    }
    void Client::connect(const std::string& ip, int port)

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

    const std::string Client::send(const std::string& str)
    {
        logger->log("sending msg:", str);

        bool res;

        // 告知服务器长度
        res = send_size(str.length());
        if (!res) return "";

        // 发送字节数据
        send_bytes((Byte*)&str, str.length());
        if (!res) return "";

        // 接受长度数据
        int nbytes = recv_size();
        if (!nbytes) return "";

        // 接受字节数
        Byte* buffer = new Byte[nbytes]{ 0 };
        res = recv_bytes(buffer, nbytes);
        if (!res) return "";

        std::string recvstr = *(std::string*)buffer;
        delete[] buffer;
        return recvstr;
    }

    bool Client::send_size(const Uint& size)
    {
        // 先发送4字节的request长度数据
        int irtn = ::send(owned_socket, &size, 4, 0);
        if (irtn < 0)
        {
            logger->log("cannot send length data");
            return false;
        }
        logger->log("told server msg_size:", size, "  bytes");
        return true;
    }
    bool Client::send_bytes(const Byte* data, const Uint& nbytes)
    {
        // 发送request
        int irtn = ::send(owned_socket, data, nbytes, 0);
        if (irtn < 0)
        {
            logger->log("unable to send data");
            return false;

        }
        logger->log(irtn, " bytes of data sent");
        return true;
    }
    const Uint Client::recv_size()
    {
        // 接收从服务器发来的response长度
        Uint recvstr_len;
        int irtn = ::recv(owned_socket, &recvstr_len, 4, MSG_WAITALL);
        if (irtn < 0)
        {
            logger->log("cannot receive length data");
            return 0;
        }
        logger->log(recvstr_len, " bytes to receive");
        return recvstr_len;
    }
    bool Client::recv_bytes(Byte* buffer, const Uint& nbytes)
    {
        // 接受response
        Byte* recv_buf = new Byte[nbytes];
        int irtn = ::recv(owned_socket, recv_buf, nbytes, MSG_WAITALL);
        if (irtn < 0)
        {
            logger->log("cannot receive data");
            return false;
        }
        logger->log("received:", recv_buf);
        memcpy(buffer, recv_buf, nbytes);
        delete[] recv_buf;
        return true;
    }

    void Client::disconnect()
    {
        if (owned_socket > 0)
            close(owned_socket);

        logger->log("connection closed");
        owned_socket = 0;

    }
    Client::~Client()
    {
        disconnect();
    }
};