#include "Json.h"
#include <iostream>

int main()
{
    using namespace std;
    using namespace quoilam;

    JsonValue json(JsonValueType::Object);

    json["123"] = string("123");

    json["456"] = 123.0;

    json["789"] = 867.0;

    std::cout << json.stringrify() << std::endl;
    return 0;
}