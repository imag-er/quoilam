#include "socket_base.h"
quoilam::socket_base::socket_base(const std::string& name_):
    name(name_)
{
    logger = std::make_shared<quoilam::StdLogger>(name_);
}

void quoilam::socket_base::handle_error(const std::string& msg)
{
    logger->log(msg, "\terrno:", errno);
    return;
}

