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

    t.interval([]() {
        std::cout << 111 << std::endl;
        }, 1s);
    t.interval([]() {
        std::cout << 222 << std::endl;
        }, 1s);
    t.timeout([]() {
        std::cout << 333 << std::endl;
        }, 5s);
    glog.log("all detached");
    while (1) {
    }
    return 0;
}