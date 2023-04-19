#include <Pipe.h>
#include <string>
#include <StdLogger.h>
int main(int argc, char **argv)
{
    // 0 receiver 1 writer
    int role = argv[1][0] - '0';

    // simplex halfduplex duplex
    int type = argv[2][0] - '0';

    using namespace quoilam;
    SimplexPipe sp("mypipe");
    switch (role)
    {
    case 0:
        std::string buffer = sp.read();
        glog.log("received: ", buffer);
        break;
    case 1:
        std::string buffer = "pipe test";
        sp.write(buffer);
        break;
    }
    return 0;
}