#include <iostream>

#include <cstdint>
#include <cstring>
#include <string>

using Byte = char;
int main()
{
    std::string s = "tewstaaaaaaaaaaaaaaaaawdawdawdawdawdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    Byte* buf = (Byte*)&s;
    std::cout << "sizeof(buf)" << sizeof(buf) << "   strlen(s)" << strlen(buf) << std::endl;
    Byte* newbuf = new Byte[24];
    memcpy(newbuf, buf, 24);
    std::string ds = *(std::string*)newbuf;
    std::cout << ds << std::endl;

    delete[] newbuf;
    return 0;
}