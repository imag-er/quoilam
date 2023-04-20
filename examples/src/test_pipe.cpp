#include <quoilam/Pipe.h>
#include <string>

#include <quoilam/StdLogger.h>
#include <unistd.h>
#include <sys/wait.h>
#include <quoilam/Typedef.h>

int main(int argc, char **argv)
{
    using namespace quoilam;
    using namespace quoilam::ultility;
    using namespace quoilam::io;

    pid_t pid = fork();
    
    if (pid > 0)
    {
        ultility::Pipe sp = Pipe("mypipe", io::iomode::read);
        glog.log("ready to receive");
        while (1)
        {
            std::string buffer = sp.read();
            if (buffer != "")
                glog.log("received: ", buffer);
        }
    }
    else
    {
        Pipe sp = Pipe("mypipe", iomode::write);
        std::string buffer;
        std::cout << "waiting for input:" << std::endl;
        std::cin >> buffer;
        sp.write(buffer);
    }
    return 0;
}