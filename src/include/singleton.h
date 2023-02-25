#pragma once

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
    static T* instance();

private:
    singleton();
    static T* pobj;
};