#include "include/server.h"
#include "include/singleton.h"
#include<iostream>
#include <string>
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
    Server s = singleton_<Server>();
    s.listen("0.0.0.0", 8888);
    s.bind("echo", echo_handler);
    s.exec();
    return 0;
}