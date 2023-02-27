#include <iostream>
#include "include/client.h"
#include "include/singleton.h"
#include <string>
int main(int, char**)
{
    using namespace quoilam;
    Client c = singleton_<Client>();
    c.connect("0.0.0.0", 25384);
    StringRequest req;
    StringResponse resp;

    req.name = "echo";
    req.str1 = "first";
    req.str2 = "second";
    resp = c.call<StringRequest, StringResponse>(req);

    // std::cout << resp->strres << std::endl;

    return 0;
}
