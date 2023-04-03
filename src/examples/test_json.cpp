#include "Json.h"
#include <iostream>

int main()
{
    using namespace std;
    using namespace quoilam;

    Json json(JsonType::Object);

    json.parse("{\"string\": \"test\",\"number\": 123.0,\"child\": {\"string\": \"test\",\"number\": 123.0}}");
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