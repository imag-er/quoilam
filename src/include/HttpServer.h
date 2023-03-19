#include "Server.h"
#include <string>
#include <functional>
namespace quoilam
{
    class HttpServer: public Server
    {
    public:
        HttpServer(std::string ip, Uint port);
        std::function<std::string(const std::string&)> process =
            [this](std::string req) -> std::string
        {
            return "HTTP/1.1 200 OK\r\nContent-Length: 14\r\n\r\nHello, World!\r\n";
        };
    protected:


        void handle_custom(
            int client_socket,
            sockaddr_in s_info
        );

        void http_response_callback(int client_socket);
    };
}