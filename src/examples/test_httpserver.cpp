#include "HttpServer.h"

int main()
{
    using namespace quoilam;
    HttpServer hs("0.0.0.0", 13824);

    hs.process = [&hs](std::string req) -> std::string
    {
        return "HTTP/1.1 200 OK\r\nContent-Length: 14\r\n\r\nHello, World!\r\n";
    };

    hs.exec();

    return 0;
}