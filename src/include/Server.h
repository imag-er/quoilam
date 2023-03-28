#pragma once
#include "SocketBase.h"
#include "StdLogger.h"
#include "ThreadPool.h"
#include <arpa/inet.h>
#include <functional>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace quoilam
{

    class Server : protected SocketBase
    {
    public:
        // 启动选项
        class Options
        {
        public:
            enum class ProtoType
            {
                quoilam_socket = 0,
                custom,
            };
            ProtoType protocol;
            bool reuse_port;
            Options(
                const ProtoType &protocol_ = Options::ProtoType::quoilam_socket,
                const bool &reuse_port_ = true)
                : protocol(protocol_),
                  reuse_port(reuse_port_)
            {
            }
        };

        // 构造函数
        Server(const Options &option = Options());

        // 设置监听
        void listen(const std::string &ip, int port);

        // 循环运行
        void exec();

        // 析构
        ~Server();

    protected:
        // 处理quoilam_socket通信
        void handle_quoilam_socket(int client_socket, sockaddr_in s_info);

        // 自定义消息处理 （为http rpc做准备）
        virtual void handle_custom(
            int client_socket,
            sockaddr_in s_info){};

        // 处理quoilam_socket的回调
        void quoilam_callback(int socket_);

        void release_socket(int socket_);

        std::shared_ptr<ThreadPool> tpool;

        std::vector<int> client_sockets;

        // 地址链接数统计 纺织数据错误接收
        Uint addr_used = 0;

    private:
        // 选项
        Options opt;
    };
};