#include "SocketBase.h"
namespace quoilam::network
{

    SocketBase::SocketBase(const std::string &name_) : name(name_)
    {
        logger = std::make_shared<io::StdLogger>(name_);
        
    }

    void SocketBase::handle_error(const std::string &msg)
    {
        logger->log(msg, "\terrno:", errno);
        return;
    }

};
