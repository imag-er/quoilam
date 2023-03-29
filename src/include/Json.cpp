#include "Json.h"
#include <iostream>
namespace quoilam
{
    JsonValue::JsonValue() : type(JsonValueType::Null) {}
    JsonValue::JsonValue(bool value) : type(JsonValueType::Boolean), jbool(value) {}
    JsonValue::JsonValue(double value) : type(JsonValueType::Number), jnumber(value) {}
    JsonValue::JsonValue(const std::string &value) : type(JsonValueType::String), jstring(new std::string(value)) {}
    JsonValue::JsonValue(const std::vector<JsonValue> &value) : type(JsonValueType::Array), jarray(new std::vector<JsonValue>(value)) {}
    JsonValue::JsonValue(const std::map<std::string, JsonValue> &value) : type(JsonValueType::Object), jobject(new std::map<std::string, JsonValue>(value)) {}

    JsonValue &JsonValue::operator=(bool value)
    {
        jbool = value;
        type = JsonValueType::Boolean;
        return *this;
    }
    JsonValue &JsonValue::operator=(double value)
    {
        jnumber = value;
        type = JsonValueType::Number;
        return *this;
    }
    JsonValue &JsonValue::operator=(const std::string &value)
    {
        jstring = new std::string(value);
        type = JsonValueType::String;

        return *this;
    }
    JsonValue &JsonValue::operator=(const std::vector<JsonValue> &value)
    {
        jarray = new std::vector<JsonValue>(value);
        type = JsonValueType::Array;

        return *this;
    }
    JsonValue &JsonValue::operator=(const std::map<std::string, JsonValue> &value)
    {
        jobject = new std::map<std::string, JsonValue>(value);
        type = JsonValueType::Object;

        return *this;
    }
    JsonValue::~JsonValue()
    {
        switch (type)
        {
        case JsonValueType::Array:
            delete jarray;
            break;
        case JsonValueType::Object:
            delete jobject;
            break;
        case JsonValueType::String:
            delete jstring;
            break;
        }
    }

    JsonValue &JsonValue::operator[](const std::string &name)
    {
        if (jobject == nullptr)
        {
            std::cout << "null object";
        }
        std::cout << "null object";
        
        (*jobject)["123"] = 123.0;

        if (!jobject->count(name))
        {
            std::cout << "cunt";

            (*jobject)[name] = JsonValue();
            std::cout << "create";
        }
        std::cout << "create11";

        return (*jobject)[name];
    }

}
