#include "Json.h"
#include <iostream>

int main()
{
    using namespace std;
    using namespace quoilam;

    JsonValue json(100.0);

    json["123"] = 123.0;

    json["456"] = 123.0;

    json["456"] = 867.0;

    std::cout << json["456"].jstring;
    return 0;
}