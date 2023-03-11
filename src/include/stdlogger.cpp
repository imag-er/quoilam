#include "stdlogger.h"

namespace quoilam
{
    stdlogger glog("program");
    stdlogger::stdlogger(const std::string& name, const char& separator):
        logger_name(name), sep(separator)
    {

    }

}