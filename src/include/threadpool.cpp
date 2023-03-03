#include "threadpool.h"

quoilam::ThreadPool::ThreadPool(const uint32_t &thread_cnt) :
    running(true)
{
    for (uint32_t i = 0; i < thread_cnt; ++i)
    {
        worker_threads.emplace_back(
            [this]()
            {
                while (true)
                {
                    task_t task;
                    {
                        // 块加锁
                        std::unique_lock<std::mutex> queue_lock{lock};
                        // 没在运行或者有任务
                        cv.wait(queue_lock,[this](){return !running || !tasks.empty();});
                        if (!running && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
    }
}

quoilam::ThreadPool::~ThreadPool()
{
    
}