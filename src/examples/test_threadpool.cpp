#include "threadpool.h"
#include "singleton.hpp"
#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
using namespace std::chrono_literals;
#include <thread>
using namespace quoilam;
using namespace std;
#include <mutex>
#include <string>
#include <vector>

int func(int index)
{
    static mutex m;
    while (1)
    {
        m.lock();
        std::cout << "\r thread: " << index
            << "\tworking threads:" << singleton<ThreadPool>::get()->running_size()
            << "\twaiting threads:" << singleton<ThreadPool>::get()->waiting_size()
            ;

        m.unlock();
        std::this_thread::sleep_for(500ms);
    }
    return 0;
}


int main()
{
    std::cout << 111;
    ThreadPool* pool = singleton<ThreadPool>::instance(16);

    auto f = [](int a, int b) {return a + b;};
    int rtn1 = pool->push_task(f, 1, 2).get();
    int rtn2 = pool->push_task(f, 10, 20).get();

    std::cout << rtn1 << '\t' << rtn2 << std::endl;

    pool->run();
    // for (int i = 0;i < 20;i++)
    // {
    //     pool->push_task(func, i);
    //     std::this_thread::sleep_for(120ms);
    // }

    while (1) {};
    return 0;

}
