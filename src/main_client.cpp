#include <iostream>
#include "include/client.h"
#include "include/singleton.hpp"
#include <string>
int main(int, char**)
{
    using namespace quoilam;
    Client c = singleton_<Client>();
    c.connect("0.0.0.0", 25384);

    std::string result = c.send("661231236");

    std::cout << "result: " << result << std::endl;

    return 0;
}
