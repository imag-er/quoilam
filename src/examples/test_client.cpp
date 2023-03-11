#include <iostream>
#include "client.h"
#include "singleton.hpp"
#include <string>
int main(int, char**)
{
    using namespace quoilam;
    Client c;
    c.connect("0.0.0.0", 25384);

    std::string result = c.send("661231236");

    glog.log("result:", result);

    return 0;
}
