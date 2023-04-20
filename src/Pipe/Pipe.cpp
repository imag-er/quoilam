#include "Pipe.h"

#include <cstdlib>
#include <unistd.h>

#include <string.h>
#include <errno.h>

#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <cstdio>

namespace quoilam::ultility
{
    Pipe::Pipe(const std::string& path,io::iomode mode)
        : logger("pipe"), success(false)
    {
        if (mode == io::iomode::write)
        {
            umask(0);
            int rtn = mkfifo(path.c_str(),S_IFIFO|0666);
            if (rtn !=0)
            {
                io::glog.log("create pipe error : ",strerror(errno));
                return ;
            }
            umask(0);

            fd = open(path.c_str(),O_WRONLY);
            
            if (fd == -1)
            {
                io::glog.log("write pipe error : ",strerror(errno));
                return ;
            }

            success = true;

        }
        else if (mode == io::iomode::read)
        {

        }

    }
    Pipe::operator const bool() const
    {
        return success;
    }

    const std::string Pipe::read()
    {
        
    }

    void Pipe::write(const std::string &data)
    {
        
    }
    Pipe::~Pipe()
    {
        close(fd);
        return;
    }

}