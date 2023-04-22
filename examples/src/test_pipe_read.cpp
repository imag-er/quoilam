#include <quoilam/Pipe.h>
#include <quoilam/StdLogger.h>
int main()
{
    QUOILAM_ALL_NAMESPACE;

    Pipe sp = Pipe("mypipe", iomode::read);

    if (!sp)
        return 1;

    glog("ready to receive");

    std::string buffer ;
    while (sp)
    {
        buffer = sp.read();

        if (buffer.empty())
            glog("read error");

        glog("received: ", buffer);
        glog("buf size:",buffer.size());
    }

    return 0;
}