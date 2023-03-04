#include "threadpool.h"

quoilam::ThreadPool::ThreadPool(const uint32_t &thread_cnt_max) : running(true), max_thread_cnt(thread_cnt_max), being_paused(true)
{

    for (uint32_t i = 0; i < thread_cnt_max; ++i)
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
                        cv.wait(queue_lock, [this]()
                                { return !being_paused; });
                        // 没在运行或者有任务
                        cv.wait(queue_lock, [this]()
                                { return !running || (!tasks.empty()); });
                        if (!running && tasks.empty())
                            return;
                        task = std::move(tasks.front());
                        tasks.pop();

                        ++(this->thread_cnt);
                    }
                    task();
                    --(this->thread_cnt);
                }
            });
    }
}

quoilam::ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> queue_lock(lock);
        running = false;
    }
    cv.notify_all();
    for (auto &thread : worker_threads)
        thread.join();
}

void quoilam::ThreadPool::run()
{
    {
        std::unique_lock<std::mutex> queue_lock(lock);
        being_paused = false;
        cv_paused.notify_all();
    }
}
void quoilam::ThreadPool::set_paused()
{
    {
        std::unique_lock<std::mutex> queue_lock(lock);
        being_paused = true;
        cv_paused.notify_all();
    }
}