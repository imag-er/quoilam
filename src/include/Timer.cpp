#include "Timer.h"


namespace quoilam
{
    Timer::Timer()
    {

    }

    Timer::Interval::Interval(std::thread& func)
    {
        id = func.get_id();
        native_handle = func.native_handle();
    }
    void Timer::Interval::kill()
    {
        pthread_cancel(native_handle);
    }
}