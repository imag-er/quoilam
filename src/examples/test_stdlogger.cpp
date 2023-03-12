#include "Singleton.hpp"
#include "StdLogger.h"

int main()
{
    auto logger = quoilam::singleton<quoilam::StdLogger>::instance("test_logger");
    logger->log("log test", "\t123123", 12312312, 4312u, 0xFF);
    
    return 0;

}