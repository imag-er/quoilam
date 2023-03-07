#include "threadpool.h"
#include "client.h"
#include <string>
#include "singleton.hpp"
#include <cstdint>
#include <vector>
#include <iostream>

// #define DISABLE_COUT
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

    for (int i = 0; i < count; i++)
    {
        Client c;
        c.connect("127.0.0.1", 25384);
        vv.push_back(std::move(c));
        pool->push_task(
            // std::bind(&Client::send, &vv[i], std::placeholders::_1),
            // teststr
            [&]()
            {
                cout << "<<" << c.send(teststr) << ">>";
            }
        );
    }

    auto begin_time = chrono::steady_clock::now();
    pool->run();
    while (pool->running_size() != 0)
    {
    };
    auto end_time = chrono::steady_clock::now();

    auto dtime = end_time - begin_time;
#ifdef DISABLE_COUT
    cout.rdbuf(buf);
#endif
    printf("本次测试%u客户端并发\t包内容:\"%s\"\t包大小:%lu\n共用时%ldus.\n",
        count, teststr.c_str(), sizeof(teststr),
        chrono::duration_cast<chrono::microseconds>(dtime).count());

    while (1)
    {
        if (pool->running_size() == 0)
        {
            cout << "所有线程都已退出" << endl;
        }
    };
    return 0;
}