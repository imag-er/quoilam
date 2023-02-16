#pragma once
template <class T>
T &singleton_();

template <typename T>
class singleton
{
public:
    static T *instance();

private:
    singleton();
    static T *pobj;
};