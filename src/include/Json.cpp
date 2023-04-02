#include "Json.h"
#include <iostream>
#include <sstream>
namespace quoilam
{
    JsonValue::JsonValue() : type(JsonValueType::Null)
    {
    }

    JsonValue::JsonValue(JsonValueType value_type)
        : type(value_type)
    {
        if (value_type == JsonValueType::Boolean)
            *this = JBool();
        if (value_type == JsonValueType::Number)
            *this = JNumber();
        if (value_type == JsonValueType::String)
            *this = JString();
        if (value_type == JsonValueType::Array)
            *this = JArray();
        if (value_type == JsonValueType::Object)
            *this = JObject();

        std::cout << "constructed\ntype:" << (int)type << std::endl;
        return;
    }

    JsonValue &JsonValue::operator=(const JBool &value)
    {
        jbool = new JBool(std::move(value));
        type = JsonValueType::Boolean;
        return *this;
    }
    JsonValue &JsonValue::operator=(const JNumber &value)
    {
        jnumber = new JNumber(std::move(value));
        type = JsonValueType::Number;
        return *this;
    }
    JsonValue &JsonValue::operator=(const JString &value)
    {
        jstring = new JString(std::move(value));
        type = JsonValueType::String;
        return *this;
    }
    JsonValue &JsonValue::operator=(const JArray &value)
    {
        jarray = new JArray(std::move(value));
        type = JsonValueType::Array;
        return *this;
    }
    JsonValue &JsonValue::operator=(const JObject &value)
    {
        jobject = new JObject(std::move(value));
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
            return *this;
        }
        return (*jobject)[name];
    }

    JBool &JsonValue::asbool()
    {
        if (type != JsonValueType::Boolean)
            throw ValueTypeError();
        return *jbool;
    }
    JNumber &JsonValue::asnumber()
    {
        if (type != JsonValueType::Number)
            throw ValueTypeError();
        return *jnumber;
    }
    JString &JsonValue::asstring()
    {
        if (type != JsonValueType::String)
            throw ValueTypeError();
        return *jstring;
    }
    JArray &JsonValue::asarray()
    {
        if (type != JsonValueType::Array)
            throw ValueTypeError();
        return *jarray;
    }

    const std::string JsonValue::stringrify() const
    {
        // std::stringstream ss;
        // ss << "{\n";
        // for (const auto& [k,v]:*jobject)
        // {
        //     ss << "\""<<k<<"\":" << v.stringrify() << ",\n";
        // }
        // ss << "}\n";
        // return ss.str();
        return "";
    }

}
