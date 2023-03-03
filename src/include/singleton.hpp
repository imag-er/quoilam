#pragma once
#include <utility>

namespace quoilam
{
    // via static variant in func
    // since c++11 , totally thread safe
    template <class T>
    T &singleton_();

    // via template class
    // async err
    template <typename T>
    class singleton
    {
    public:
        template <class... Args>
        static T &instance(Args &&...args)
        {
            if (pobj == nullptr)
                pobj = new T(std::forward<Args>(args)...);

            return *pobj;
        }
        static T &instance()
        {
            if (pobj == nullptr)
                pobj = new T();

            return *pobj;
        }

        T& get()
        {
            return *pobj;
        }
        void destroy()
        {
            delete pobj;
            pobj = nullptr;
        }

    private:
        singleton() {}
        static T *pobj;
    };

    template <class T>
    T *singleton<T>::pobj = nullptr;

    template <class T, class... Args>
    inline T &singleton_(Args &&...args)
    {
        static T instance(std::forward<Args>(args)...);
        return instance;
    }
    
    template <class T>
    inline T &singleton_()
    {
        static T instance;
        return instance;
    }

}