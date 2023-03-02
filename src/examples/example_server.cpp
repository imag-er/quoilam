#include "server.h"
#include "singleton.hpp"
#include <iostream>
#include <string>

int main()
{
    using namespace quoilam;
    Server s = singleton<Server>::instance();
    s.listen("0.0.0.0", 25384);
    s.exec();
    return 0;
}