#include <iostream>
#include "include/client.h"
#include "include/singleton.hpp"
#include <string>
int main(int, char**)
{
    using namespace quoilam;
    Client c = singleton_<Client>();
    c.connect("0.0.0.0", 25384);

    resp = c.send(req);

    std::cout << resp.strres << std::endl;

    return 0;
}
