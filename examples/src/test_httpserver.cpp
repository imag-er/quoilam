#include <quoilam/HttpServer.h>

int main()
{
    using namespace quoilam::network;
    HttpServer hs("0.0.0.0", 13824);
    hs.exec();
    return 0;
}