#include <iostream>
#include <quoilam/Client.h>
#include <quoilam/Singleton.hpp>
#include <string>
int main(int, char**)
{
    QUOILAM_ALL_NAMESPACE;
    
    Client c;
    c.connect("0.0.0.0", 25384);

    std::string result = c.send("661231236");

    glog.log("result:", result);

    return 0;
}
