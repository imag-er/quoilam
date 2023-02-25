#include <iostream>
#include "client.h"
#include "singleton.h"
#include <string>
int main(int, char**)
{
    Client c = singleton_<Client>();
    c.connect("0.0.0.0", 8888);
    StringRequest req;
    StringResponse resp;

    req.name = "echo";
    req.str1 = "first";
    req.str2 = "second";
    resp = c.call<StringResponse>(&req);

    std::cout << resp.strres << std::endl;

    return 0;
}
