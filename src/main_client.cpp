#include <iostream>
#include "client.h"
#include "singleton.h"
#include <string>
int main(int, char**)
{
    using namespace quoilam;
    Client c = singleton_<Client>();
    c.connect("0.0.0.0", 8888);
    StringRequest::Ptr req;
    StringResponse::Ptr resp;

    req->name = "echo";
    req->str1 = "first";
    req->str2 = "second";
    resp = dynamic_cast<StringResponse*>(c.call(req));

    std::cout << resp->strres << std::endl;

    return 0;
}
