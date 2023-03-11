#pragma once
#include "inner_logger.hpp"
namespace quoilam
{
    class stdlogger: private inner_logger
    {

    public:
        stdlogger(const std::string& name, const char& separator = '\t');

        template <class... Args>
        void log(Args... args)
        {
            std::cout << '[' << logger_name << ']';
            inner_log(args...);
        }
    private:
        const std::string logger_name;
        const char sep;
    };

    extern stdlogger glog;
};