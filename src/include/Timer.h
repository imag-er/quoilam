#include <chrono>
#include <future>
#include <functional>
#include <thread>
#include <future>
#include "StdLogger.h"
namespace quoilam
{

    class Timer
    {
    public:
        Timer();

        class Interval
        {
        public:
            Interval(std::thread &func);
            std::thread::id id;
            void kill();

        protected:
            pthread_t native_handle;
        };

        template <class Func, class... Argu>
        auto timeout(
            Func &&f,
            std::chrono::duration<uint32_t, std::milli> period,
            Argu &&...argus) -> std::future<decltype(f(argus...))>;

        template <class Func, class... Argu>
        Interval interval(
            Func &&f,
            std::chrono::duration<uint32_t, std::milli> claps,
            Argu &&...argus);

    private:
    protected:
    };

    template <class Func, class... Argu>
    auto Timer::timeout(
        Func &&f,
        std::chrono::duration<uint32_t, std::milli> period,
        Argu &&...argus) -> std::future<decltype(f(argus...))>
    {
        using ReturnType = decltype(f(argus...));
        auto task = std::bind(std::forward<Func>(f), std::forward<Argu>(argus)...);
        std::promise<ReturnType> prom;

        auto sync_task = [&task,prom_ = std::move(prom)]()
        {
              prom_.set_value(task());
              return prom.get_future();
        };

        std::thread(sync_task).detach();
        glog.log("timeout thread id:", std::this_thread::get_id(), " started");
        return prom.get_future();

        /*
        #include <iostream>
#include <thread>
#include <future>

template<typename Func, typename... Args>
auto async(Func&& func, Args&&... args)
{
    using result_type = std::invoke_result_t<Func, Args...>;
    std::promise<result_type> promise;
    auto future = promise.get_future();

    std::thread thread([promise = std::move(promise), func = std::forward<Func>(func), ...args = std::forward<Args>(args)]() mutable {
        try {
            promise.set_value(std::invoke(func, std::forward<Args>(args)...));
        }
        catch (...) {
            promise.set_exception(std::current_exception());
        }
    });

    return std::make_pair(std::move(thread), std::move(future));
}

int add(int a, int b)
{
    return a + b;
}

int main()
{
    auto [thread, future] = async(add, 1, 2);

    int result = future.get();
    std::cout << "Result: " << result << std::endl;

    thread.join();
    return 0;
}

        */
    }

    template <class Func, class... Argu>
    Timer::Interval Timer::interval(
        Func &&f,
        std::chrono::duration<uint32_t, std::milli> claps,
        Argu &&...argus)
    {
        // 这里不用线程池是因为Timer非单例 线程池管理不方便
        // 而且并没有高频率的创建/销毁 对性能要求并不高
        auto ff = [&]()
        {
            while (1)
                timeout(f, claps, argus...);
        };
        std::thread t(ff);
        Interval v(t);
        t.detach();
        glog.log("interval thread id:", std::this_thread::get_id(), " detached");

        return v;
    }
};