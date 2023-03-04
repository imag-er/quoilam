#include <thread>
#include <functional>
#include <memory>
#include <queue>
#include <future>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <type_traits>
namespace quoilam
{
    class ThreadPool
    {
    public:
        ThreadPool(const uint32_t &thread_cnt_max);

        // 禁止拷贝 移动
        ThreadPool(const ThreadPool &) = delete;
        ThreadPool(const ThreadPool &&) = delete;
        ThreadPool &operator=(const ThreadPool &) = delete;
        ThreadPool &operator=(const ThreadPool &&) = delete;

        ~ThreadPool();

        const uint32_t running_size() const { return thread_cnt; }
        const uint32_t waiting_size() const { return tasks.size(); }
        const uint32_t max_size() const { return max_thread_cnt; }
        const bool is_running() const { return running; }

        void run();
        void set_paused();

        template <class F, class... Args>
        auto push_task(F &&f, Args &&...args) -> std::future<decltype(f(args...))>;

    private:
        using task_t = std::function<void()>;

        const uint32_t max_thread_cnt;

        std::atomic_bool being_paused;
        std::atomic_bool running;
        std::atomic_uint32_t thread_cnt;
        std::queue<task_t> tasks;
        std::mutex lock;
        std::vector<std::thread> worker_threads;

        std::condition_variable cv;
        std::condition_variable cv_paused;
    };

    template <class F, class... Args>
    auto ThreadPool::push_task(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        using return_t = decltype(f(args...));
        using pkg_task_t = std::packaged_task<return_t()>;

        auto task_ptr = std::make_shared<pkg_task_t>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        {
            // lock_guard对当前块加锁 所以这里有一对奇怪的括弧
            std::lock_guard<std::mutex> queue_lock{lock};
            tasks.emplace([task_ptr]()
                          { (*task_ptr)(); });
        }

        // 唤醒线程
        cv.notify_one();

        return task_ptr->get_future();
    }

}