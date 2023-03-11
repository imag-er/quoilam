#include "threadpool.h"
#include "client.h"
#include <string>
#include "singleton.hpp"
#include <cstdint>
#include <vector>
#include <iostream>
#include "stdlogger.h"
#define DISABLE_COUT
int main(int argc, char** argv)
{
    using namespace std;
    using namespace quoilam;

    mutex m;
    if (argc < 2)
    {
        cout << "too few arguments" << endl;
        return 1;
    }
#ifdef DISABLE_COUT
    auto buf = cout.rdbuf();
    cout.rdbuf(nullptr);
#endif
    uint32_t count = atoi(argv[1]);
    vector<Client> vv;
    string teststr = "测试字符串";
    ThreadPool* pool = singleton<ThreadPool>::instance(count);


    auto begin_time = chrono::steady_clock::now();
    for (int i = 0; i < count; i++)
    {

        vv.push_back(Client());
        pool->push_task(
            [&m](Client c, const std::string str)
            {
                m.lock();
                c.connect("127.0.0.1", 25384);
                glog.log(c.send(str));
                m.unlock();
            },
            vv.back(), teststr
                );
    }
    while (pool->running_size() != 0)
    {
    };
    auto end_time = chrono::steady_clock::now();

    auto dtime = end_time - begin_time;


    delete pool;
    vv.clear();
#ifdef DISABLE_COUT
    cout.rdbuf(buf);
#endif
    printf("本次测试%u客户端并发\t包内容:\"%s\"\t包大小:%lu\n共用时%fms.\n",
        count, teststr.c_str(), sizeof(teststr),
        std::chrono::duration<double, std::milli>(dtime).count());
    return 0;
}