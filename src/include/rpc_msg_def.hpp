#pragma once
#include <string>



class Request
{
public:
    std::string name;
};
class Response
{
public:
    std::string name;
};




class StringRequest: public Request
{
public:
    std::string str1, str2;
};

class StringResponse: public Response
{
public:
    std::string strres;
};