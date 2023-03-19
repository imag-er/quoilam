#pragma once
#include <string>
#include <functional>
#include <sys/socket.h>
#include "ThreadPool.h"
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "StdLogger.h"
#include "SocketBase.h"
namespace quoilam
{

    class Server: protected SocketBase
    {
    public:

        // 启动选项
        class Options
        {
        public:
            bool custom = false;
        };

        // 构造函数
        Server(const Options& option = Options{ false });

        // 设置监听
        void listen(const std::string& ip, int port);

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
            sockaddr_in s_info)
        {};

        // 处理quoilam_socket的回调
        void listen_callback(int socket_);

        std::shared_ptr<ThreadPool> tpool;

    private:
        // 选项
        Options opt;
        // 线程池

    };
};