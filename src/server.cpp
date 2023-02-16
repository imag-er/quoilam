#include "include/server.h"
#include<iostream>
#include <string>
std::string echo_handler(const std::string& str)
{
    return str;
}
int main()
{
    Server* s = singleton_<Server>();
    s->listen("0.0.0.0",8888);
    s->bind("echo",echo_handler);
    s->exec();
    return 0;
}