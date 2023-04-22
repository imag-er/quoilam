#include <quoilam/Singleton.hpp>
#include <quoilam/StdLogger.h>

int main()
{
    using namespace quoilam::io;
    using namespace quoilam::util;
    
    auto logger = singleton<StdLogger>::instance("test_logger");
    logger->log("log test", "\t123123", 12312312, 4312u, 0xFF);

    glog("测试");
    return 0;

}