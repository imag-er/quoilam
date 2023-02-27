#include <iostream>


class father
{
};

class son: public father
{
};



int main()
{
    son s;
    std::cout << &s << std::endl;
    print(&s);

    return 0;
}