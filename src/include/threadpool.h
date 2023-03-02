#include <thread>
#include <functional>
#include <memory>
#include <queue>
#include <future>
#include <mutex>
#include <condition_variable>
namespace quoilam
{
    class ThreadPool
    {
    public:
        ThreadPool(int thread_cnt);

        ~ThreadPool();

        template<class F, class... Args>
        auto push_task(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;



    private:
        std::queue<std::function<void()>> tasks;
        std::mutex lock;
        std::vector<std::thread> worker_threads;
        std::condition_variable cv;
    };
    template<class F, class... Args>
    auto ThreadPool::push_task(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
    {
        using return_t = decltype(f(args...));
        using task_t = decltype(std::packaged_task<return_t>);

        auto task_ptr = std::make_shared<task_t>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

    


    }

}