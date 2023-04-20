#include <quoilam/Server.h>
#include <quoilam/Singleton.hpp>

int main()
{
    QUOILAM_ALL_NAMESPACE;
    Server* s = singleton<Server>::instance();
    s->listen("0.0.0.0", 25384);
    s->exec();
    return 0;
}

