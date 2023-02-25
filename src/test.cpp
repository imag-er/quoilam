#include <iostream>


class father
{
public:
    int placeholder = 1;
};

class son: public father
{

public:
    int placeholder_ = 2;
};

void print(father* f)
{
    std::cout << ((son*)f)->placeholder_ << std::endl;
    std::cout << f;
    return;
}

int main()
{
    son s;
    std::cout << &s << std::endl;
    print(&s);

    return 0;
}