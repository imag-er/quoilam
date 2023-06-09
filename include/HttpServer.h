#include "Server.h"
#include <functional>
#include <string>
namespace quoilam::network
{
#ifndef _WIN32
    class HttpServer : public Server
    {
    public:
        HttpServer(std::string ip, UInt port);
        std::function<std::string(std::string)> process =
            [this](std::string req) -> std::string
        {
            static int count = 0;
            return "HTTP/1.1 200 OK\r\nContent-Length: 108\r\n\r\n"
                   "<!DOCTYPE HTML>\r\n"
                   "<html>\r\n"
                   "<head>\r\n"
                   "<meta charset=\"utf-8\">\r\n"
                   "</head>\r\n"
                   "<body>\r\n"
                   "<h1>\r\n"
                   "HelloWorld" +
                   std::to_string(count++) +
                   "\r\n"
                   "</h1>\r\n"
                   "</body>\r\n"
                   "</html>\r\n";
        };

    protected:
        void handle_custom(
            int client_socket,
            sockaddr_in s_info);

        void http_response_callback(int client_socket);
    };
#endif
}