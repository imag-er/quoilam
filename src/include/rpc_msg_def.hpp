#pragma once
#include <string>

#define MSG_DEF(x) \ 
using Ptr = x*;

namespace quoilam
{

    class Request
    {
    public:
        std::string name;
        using Ptr = Request*;
        virtual ~Request() = default;
    };
    class Response
    {
    public:
        std::string name;
        using Ptr = Response*;
        virtual ~Response() = default;
    };


    class StringRequest: public Request
    {
    public:
        MSG_DEF(StringRequest)
            std::string str1, str2;
    };

    class StringResponse: public Response
    {
    public:
        MSG_DEF(StringResponse)

            std::string strres;
    };
}
