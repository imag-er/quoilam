#pragma once

namespace quoilam
{
    // via static variant in func
    // since c++11 , totally thread safe
    template <class T>
    T& singleton_();

    // via template class
    // async err
    template <typename T>
    class singleton
    {
    public:
        static T& instance()
        {
            if (pobj == nullptr)
            {
                pobj = new T();
            }
            return *pobj;
        }

    private:
        singleton()
        {

        }
        static T* pobj;
    };

    template <class T>
    inline T& singleton_()
    {
        static T instance;
        return instance;
    }

    template<class T>
    T* singleton<T>::pobj = nullptr;
}