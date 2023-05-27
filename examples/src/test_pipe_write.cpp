#include <quoilam/Pipe.h>

int main(int argc, char **argv)
{
    QUOILAM_ALL_NAMESPACE;

    Pipe sp = Pipe("mypipe", iomode::write);

    if (!sp)
        return 1;

    std::string buffer;
    while (buffer !="quit")
    {
        glog("waiting for input:");
        std::cin >> buffer;
        UInt wlen = sp.write(buffer);
        glog("buf size:",buffer.size()," wrote:",wlen);
    }

    return 0;
}
