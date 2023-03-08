#pragma once 
#include <string>
#include <iostream>
namespace quoilam
{
    class stdlog
    {
    public:

        stdlog(const std::string&& name, const char& separator = '\t');


        template <class... Args>
        void log(Args&&... msgs);
    private:
        template<class First>
        void inner_log(First&& first);

        template <class First, class... Args>
        void inner_log(First&& first, Args&&... args);

        const char sep;
        const std::string logger_name;
    };
};

template <class... Args>
void quoilam::stdlog::log(Args&&... msgs)
{
    std::cout << '[' << logger_name << ']';
    inner_log(msgs...);
}

template <class First, class... Args>
void quoilam::stdlog::inner_log(First&& first, Args&&... args)
{
    std::cout << first;
    if (sizeof...(args) > 0)
        inner_log(args...);
    return;
}

template<class First>
void quoilam::stdlog::inner_log(First&& first)
{
    std::cout << first << std::endl;
}