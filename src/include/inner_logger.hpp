#pragma once 
#include <string>
#include <iostream>
namespace quoilam
{
    class inner_logger
    {
    public:
        template<class First>
        static void inner_log(First&& first);

        template <class First, class... Args>
        static void inner_log(First&& first, Args&&... args);

    };
};


template <class First, class... Args>
void quoilam::inner_logger::inner_log(First&& first, Args&&... args)
{
    std::cout << first;
    if (sizeof...(args) > 0)
        inner_log(args...);
    return;
}

template<class First>
void quoilam::inner_logger::inner_log(First&& first)
{
    std::cout << first << std::endl;
}