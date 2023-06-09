#include "Pipe.h"

#include <cstdlib>
#include <unistd.h>

#include <string.h>
#include <errno.h>

#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <cstdio>

namespace quoilam::util
{
#ifndef _WIN32
    Pipe::Pipe(const std::string &path, io::iomode mode)
        : pipe_name(path), logger(path), success(false), pipe_iomode(mode)
    {
        if (mode == io::iomode::write)
        {
            int rtn = mkfifo(path.c_str(), S_IFIFO | 0666);
            if (rtn != 0)
            {
                logger("create pipe error : ", strerror(errno));
                return;
            }
            logger("successfully created pipe");

            logger("waiting for readside...");

            fd = ::open(path.c_str(), O_WRONLY);

            if (fd < 0)
            {
                logger("write pipe error : ", strerror(errno));
                return;
            }

            logger("successfully opened pipe");

            success = true;
        }
        else if (mode == io::iomode::read)
        {
            logger("waiting for writeside...");

            fd = ::open(path.c_str(), O_RDONLY);

            if (fd < 0)
            {
                logger("open pipe for read error : ", strerror(errno));
                return;
            }

            logger("successfully opened pipe");

            success = true;
        }
    }
    Pipe::operator const bool() const
    {
        return success;
    }

    const std::string Pipe::read()
    {
        std::string ret;
        if (pipe_iomode != io::iomode::read)
        {
            logger("pipe io mode error");
            return ret;
        }
        std::shared_ptr<Byte> buffer(new Byte[4096]{0});
        UInt len = ::read(fd, buffer.get(), 4096);

        if (len == 0)
        {
            // EOF
            success = false;
            return ret;
        }
        if (len < 0)
        {
            // read error
            success = false;
            return ret;
        }

        ret.assign(buffer.get(), len);

        return ret;
    }

    UInt Pipe::write(const std::string &data)
    {
        if (pipe_iomode != io::iomode::write)
        {
            logger("pipe io mode error");
            return -1;
        }
        UInt len = ::write(fd, data.c_str(), data.length());
        if (len <= 0)
        {
            logger("write pipe error : ", strerror(errno));
            success = false;
        }

        return len;
    }
    Pipe::~Pipe()
    {
        close(fd);
        if (pipe_iomode == io::iomode::write)
        {
            int ret = unlink(pipe_name.c_str());
            // 判断是否成功删除管道
            if (ret == -1)
                logger("failed to unlink pipe, error: ", strerror(errno));
            else
                logger("successfully unlinked pipe");
        }
        return;
    }

#endif
}
