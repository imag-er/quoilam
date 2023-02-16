#include <iostream>
#include "client.h"
#include <string>
int main(int, char **)
{
    Client c = singleton_<Client>();
    c->connect("0.0.0.0",8888);
    std::string call_text="123";
    std::string reply = c->call<std::string>("echo",call_text);
    

    return 0;
}
