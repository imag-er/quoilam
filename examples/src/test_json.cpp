#include "Json.h"
#include <iostream>
#include <fstream>
int main(int argc,char**argv)
{
    using namespace std;
    using namespace quoilam;

    Json json(JsonType::Object);

    std::ifstream ifs("/home/sm/quoilam/build/executable/11.json");
    if (!ifs) return 1;
    std::string str, cache;
    while (!ifs.eof())
    {
        ifs >> cache;
        str += cache;
    }
    std::cout << "read str:\n"
              << str << std ::endl;
    json.parse(str);

    // json["str"] = JString("hello world");

    // json["number"] = JNumber(123.0);

    // json["boolean"] = JBool(true);

    // json["array"] = JArray{Json(12222.0), JString("hello"), json["boolean"]};

    // json["boolean"] = JBool(false);

    // json["object"] = json;

    // json["null"] = Json(JsonType::Null);

    std::cout << json.stringrify() << std::endl;
    return 0;
}