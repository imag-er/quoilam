#include <chrono>
#include <future>
#include <functional>
namespace quoilam
{

    class Timer
    {
    public:
        Timer();

        template < class Func, class... Argu>
        auto timeout(
            Func&& f,
            std::chrono::duration<uint32_t, std::milli>&& period,
            Argu&&... argus
        ) -> decltype(f(argus...));

        template < class Func, class... Argu>
        auto async(
            Func&& f,
            Argu&&... argus
        ) -> std::future<decltype(f(argus...))>;

    private:

    protected:
    };

    template < class Func, class... Argu>
    auto Timer::timeout(
        Func&& f,
        std::chrono::duration<uint32_t, std::milli>&& period,
        Argu&&... argus
    ) -> decltype(f(argus...))
    {
        std::this_thread::sleep_for(period);
        auto sync_task = std::bind(std::forward<Func>(f), std::forward<Argu>(argus)...);
        return sync_task();
    }


    template < class Func, class... Argu>
    auto Timer::async(
        Func&& f,
        Argu&&... argus
    ) -> std::future<decltype(f(argus...))>
    {
        // 这里打包了f(args...)并且把它作为函数返回值
        using task_type = std::packaged_task<decltype(f(argus...))(void)>;

        auto async_task = std::make_shared<task_type>(
            std::bind(std::forward<Func>(f), std::forward<Argu>(argus)...)
        );

        return async_task->get_future();
    }

};


