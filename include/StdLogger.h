#pragma once
#include <memory>
#include <iostream>
namespace quoilam
{
    class InnerLogger
    {
    protected:
        template <class First>
        static void inner_log(First &&first);

        template <class First, class... Args>
        static void inner_log(First &&first, Args &&...args);
    };


    class StdLogger : private InnerLogger
    {

    public:
        StdLogger(const std::string &name, const char &separator = '\t');

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

    template <class First, class... Args>
    void InnerLogger::inner_log(First &&first, Args &&...args)
    {
        std::cout << first;
        if (sizeof...(args) > 0)
            inner_log(args...);
        return;
    }

    template <class First>
    void InnerLogger::inner_log(First &&first)
    {
        std::cout << first << std::endl;
    }

    extern StdLogger glog;

};