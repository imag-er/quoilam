#include "include/server.h"
#include "include/singleton.h"
#include <iostream>
#include <string>
using namespace quoilam;
Response* echo_handler(Request* str)
{
    StringRequest* req = (StringRequest*)str;
    StringResponse* resp;
    resp->name = "echo";
    resp->strres = req->str1 + req->str2;
    return resp;
}
int main()
{
    // quoilam::Server s = singleton_<quoilam::Server>();

    // quoilam::Server s = quoilam::singleton_<quoilam::Server>();
    Server s = *singleton<Server>::instance();
    s.listen("0.0.0.0", 25384);
    s.bind("echo", echo_handler);
    s.exec();
    return 0;
}