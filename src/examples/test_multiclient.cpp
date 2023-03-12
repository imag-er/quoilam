#include "ThreadPool.h"
#include "Client.h"
#include <string>
#include "Singleton.hpp"
#include <cstdint>
#include <vector>
#include <iostream>
#include "StdLogger.h"
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

    double time_sum = 0.0;

    for (int i = 0; i < count; i++)
    {

        vv.push_back(Client());
        pool->push_task(
            [&](Client c, const std::string str)
            {
                m.lock();
                c.connect("127.0.0.1", 25384);

                auto begin_time = chrono::steady_clock::now();
                glog.log(c.send(str));
                auto end_time = chrono::steady_clock::now();

                time_sum += std::chrono::duration<double, std::milli>(end_time - begin_time).count();
                m.unlock();
            },
            vv.back(), teststr
                );
    }
    while (pool->running_size() != 0)
    {
    };


    delete pool;
    vv.clear();
#ifdef DISABLE_COUT
    cout.rdbuf(buf);
#endif
    printf("本次测试%u客户端并发\n包内容:\"%s\"\n包大小:%lu\n共用时%fms.\n",
        count, teststr.c_str(), sizeof(teststr),
        time_sum);
    return 0;
}