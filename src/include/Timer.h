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
            Interval(std::thread& func);
            std::thread::id id;
            void kill();

        protected:
            pthread_t native_handle;
        };

        template <class Func, class... Argu>
        auto timeout(
            Func&& f,
            std::chrono::duration<uint32_t, std::milli> period,
            Argu &&...argus) -> decltype(f(argus...));

        template <class Func, class... Argu>
        Interval interval(
            Func&& f,
            std::chrono::duration<uint32_t, std::milli> claps,
            Argu &&...argus);

    private:
    protected:
    };



    template<class Func, class ...Argu>
    inline auto Timer::timeout(
        Func&& f,
        std::chrono::duration<uint32_t, std::milli> period,
        Argu && ...argus) -> decltype(f(argus...))
    {
        std::this_thread::sleep_for(period);
        auto sync_func = std::bind(std::forward<Func>(f), std::forward<Argu>(argus)...);

        return sync_func();
    }

    template <class Func, class... Argu>
    Timer::Interval Timer::interval(
        Func&& f,
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