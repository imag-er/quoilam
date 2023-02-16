#include "singleton.h"

template <class T>
T &singleton_()
{
    static T instance;
    return instance;
}

template<class T>
T* singleton<T>::pobj=nullptr;

template <class T>
T *singleton<T>::instance()
{

    if (pobj == nullptr)
    {
        pobj = new T();
    }
    return pobj;
}

template<class T>
singleton<T>::singleton()
{}
