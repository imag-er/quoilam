#include "threadpool.h"
#include "singleton.hpp"
int main()
{
    quoilam::ThreadPool pool = quoilam::singleton_<quoilam::ThreadPool>();

}