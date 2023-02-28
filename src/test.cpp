#include <iostream>

#include <cstdint>
#include <string>
using Byte = char;
int main()
{
    std::string s = "tewst";
    Byte* buf = (Byte*)&s;
    std::cout<<"sizeof(s)"<<sizeof(s) << "   strlen(s)" << strlen(buf) << std::endl;
    Byte *newbuf = new Byte[6];
    memcpy(newbuf,buf,6);
    std::string ds = *(std::string*)newbuf;
    std::cout<<ds<<std::endl;

    delete[] newbuf;
    return 0;
}