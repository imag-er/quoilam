#include "socket_base.h"
quoilam::socket_base::socket_base(const std::string& name_):
    name(name_)
{
    // logger = std::make_shared<quoilam::stdlogger>(name_);
}
bool quoilam::socket_base::handleret(
    const int& return_value,
    const std::string& success_msg,
    const std::string& failed_msg
)
{
    if (return_value > 0)
    {
        handle_success(success_msg);
        return true;
    }

    if (return_value < 0)
    {
        handle_error(failed_msg);
        return false;
    }

    if (return_value == 0)
    {
        handle_connection_lost();
        return false;
    }
}
void quoilam::socket_base::handle_success(const std::string& msg)
{
    glog.log(msg);
    return;
}

void quoilam::socket_base::handle_error(const std::string& msg)
{
    glog.log(msg, "\terrno:", errno);
    return;
}

void quoilam::socket_base::handle_connection_lost()
{
    glog.log("connection lost");
}