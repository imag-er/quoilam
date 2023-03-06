#include "threadpool.h"
#include "client.h"
#include <string>
#include "singleton.hpp"
#include <cstdint>
#include <vector>
#include <iostream>
int main(int argc, char **argv)
{
    using namespace std;
    using namespace quoilam;
    if (argc < 2)
    {
        cout << "too few arguments" << endl;
        return 1;
    }
    auto buf = cout.rdbuf();
    cout.rdbuf(nullptr);

    uint32_t count = atoi(argv[1]);
    vector<Client> vv;
    string teststr = "测试字符串";
    ThreadPool *pool = singleton<ThreadPool>::instance(count);

    for (int i = 0; i < count; i++)
    {
        vv.push_back(Client());
        vv.back().connect("127.0.0.1", 25384);
        pool->push_task([&](string test_text)
                        { vv.back().send(test_text); },
                        teststr);
    }

    auto begin_time = chrono::steady_clock::now();
    pool->run();
    while (pool->running_size() != 0)
    {
    };
    pool->set_paused();
    auto end_time = chrono::steady_clock::now();

    auto dtime = end_time - begin_time;

    cout.rdbuf(buf);
    printf("本次测试%u客户端并发\t包内容:\"%s\"\t包大小:%lu\n共用时%ldus.\n",
           count, teststr.c_str(), sizeof(teststr),
           chrono::duration_cast<chrono::microseconds>(dtime).count());

    return 0;
}