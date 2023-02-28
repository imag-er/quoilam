#include "include/server.h"
#include "include/singleton.hpp"
#include <iostream>
#include <string>
using namespace quoilam;

int main()
{
    Server s = singleton<Server>::instance();
    s.listen("0.0.0.0", 25384);
    s.exec();
    return 0;
}