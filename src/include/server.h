#pragma once
#include <string>
#include <functional>
namespace quoilam
{
    using Byte = char;

    class Server
    {
    public:
        Server();
        void listen(const std::string& ip, int port);
        void exec();

        void listen_callback(int socket_);

        ~Server();
    protected:
        void byte_explain(const Byte* input,Byte* output,const int& input_len);


        int listen_socket;
    };
};