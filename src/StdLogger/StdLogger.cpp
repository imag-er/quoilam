#include "StdLogger.h"

namespace quoilam::io
{
    StdLogger glog("program");

    StdLogger::StdLogger(const std::string& name, const char& separator):
        logger_name(name), sep(separator)
    {   
        
    }

}