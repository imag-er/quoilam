#pragma once
#include <memory>
#include <iostream>
#include "Typedef.h"
namespace quoilam::io
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

        template <class... Args>
        void operator()(Args... args);
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

    template <class... Args>
    void StdLogger::operator()(Args... args)
    {
        this->log(std::forward<Args>(args)...);
    }


    extern StdLogger glog;

};