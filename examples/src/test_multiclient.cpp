#include <quoilam/ThreadPool.h>
#include <quoilam/Client.h>
#include <string>
#include <quoilam/Singleton.hpp>
#include <cstdint>
#include <vector>
#include <iostream>
#include <quoilam/StdLogger.h>

#define DISABLE_COUT
int main(int argc, char **argv)
{
    using namespace std;
    QUOILAM_ALL_NAMESPACE;

    mutex m;
    if (argc < 3)
    {
        cout << "too few arguments" << endl;
        return 1;
    }

#ifdef DISABLE_COUT
    auto buf = cout.rdbuf();
    cout.rdbuf(nullptr);
#endif

    // 客户端数目
    uint32_t count = atoi(argv[1]);
    // 检查回复准确性
    bool check_response = strcmp(argv[2], "false");
    Uint correct_count = 0;

    vector<Client> vv;
    string teststr = "测试字符串";
    ThreadPool *pool = singleton<ThreadPool>::instance(count);

    double time_sum = 0.0;

    for (int i = 0; i < count; i++)
    {

        vv.push_back(Client());
        pool->push_task(
            [&](Client &c, const std::string &str)
            {
                m.lock();
                c.connect("127.0.0.1", 25384);

                string resp;
                auto begin_time = chrono::steady_clock::now();
                resp = c.send(str);
                auto end_time = chrono::steady_clock::now();

                if (check_response)
                    if (resp == str)
                    {
                        ++correct_count;
                    }

                time_sum += std::chrono::duration<double, std::milli>(end_time - begin_time).count();
                m.unlock();
            },
            vv.back(), teststr);
    }
    while (pool->running_size() != 0)
    {
    };

    delete pool;
    vv.clear();
#ifdef DISABLE_COUT
    cout.rdbuf(buf);
#endif
    glog.log("本次测试", count, "客户端并发\n");
    glog.log("包内容:\"", teststr, "\"\t包大小:", sizeof(teststr), "\n");
    glog.log("用时:", time_sum, "ms\t");
    glog.log("准确率:", (check_response ? ((double)correct_count / (double)count) : -1));

    return 0;
}