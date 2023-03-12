#pragma once
#include "InnerLogger.hpp"
#include <memory>
namespace quoilam
{
    class StdLogger: private InnerLogger
    {

    public:
        StdLogger(const std::string& name, const char& separator = '\t');

        template <class... Args>
        void log(Args... args)
        {
            std::cout << '[' << logger_name << ']';
            inner_log(args...);
        }

        using SharedPtr = std::shared_ptr<StdLogger>;

    protected:
        const std::string logger_name;
        const char sep;
    };

    extern StdLogger glog;
};