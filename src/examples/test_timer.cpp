#include "Timer.h"
#include  <iostream>
int f(int a, int b)
{
    return a + b;
}
int main()
{
    using namespace quoilam;
    using namespace std::chrono_literals;

    Timer t;
    auto res = t.async(f, 300, 4000).get();
    std::cout << res;
    while (1)
    {
        std::cout << '\r' << 1;

        // if (res.valid()) std::cout << res.get();
    }
    return 0;
}