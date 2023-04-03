#include "Json.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
namespace quoilam
{
    Json::Json(const Json &value)
    {
        switch (value.type)
        {
        case JsonType::Array:
            jarray = new JArray(value.asarray());
            break;
        case JsonType::Object:
            jobject = new JObject(value.asobject());
            break;
        case JsonType::Number:
            jnumber = new JNumber(value.asnumber());
            break;
        case JsonType::Boolean:
            jbool = new JBool(value.asbool());
            break;
        case JsonType::String:
            jstring = new JString(value.asstring());
            break;
        }

        type = value.type;
    }
    Json::Json(const Json &&value)
    {
        *this = std::move(value);
    }
    Json &Json::operator=(const Json &value)
    {
        // 拷贝构造 为值创建副本
        // 在对象拷贝时创建新副本 使得对象之间不共享内存
        // 防止垃圾多次回收造成segmentation fault
        switch (value.type)
        {
        case JsonType::Array:
            jarray = new JArray(value.asarray());
            break;
        case JsonType::Object:
            jobject = new JObject(value.asobject());
            break;
        case JsonType::Number:
            jnumber = new JNumber(value.asnumber());
            break;
        case JsonType::Boolean:
            jbool = new JBool(value.asbool());
            break;
        case JsonType::String:
            jstring = new JString(value.asstring());
            break;
        }
        type = value.type;
        return *this;
    }
    const Json Json::copy() const
    {
        return (*this);
    }

    Json::Json(JsonType value_type)
        : type(value_type)
    {
        if (value_type == JsonType::Boolean)
            *this = JBool();
        if (value_type == JsonType::Number)
            *this = JNumber();
        if (value_type == JsonType::String)
            *this = JString();
        if (value_type == JsonType::Array)
            *this = JArray();
        if (value_type == JsonType::Object)
            *this = JObject();
        return;
    }

    Json &Json::operator=(const JBool &value)
    {
        jbool = new JBool(value);
        type = JsonType::Boolean;
        return *this;
    }
    Json &Json::operator=(const JNumber &value)
    {
        jnumber = new JNumber(value);
        type = JsonType::Number;
        return *this;
    }
    Json &Json::operator=(const JString &value)
    {
        jstring = new JString(value);
        type = JsonType::String;
        return *this;
    }
    Json &Json::operator=(const JArray &value)
    {
        jarray = new JArray(value);
        type = JsonType::Array;
        return *this;
    }
    Json &Json::operator=(const JObject &value)
    {
        jobject = new JObject(value);
        type = JsonType::Object;
        return *this;
    }

    Json::Json(const JArray &&value)
    {
        type = JsonType::Array;
        jarray = new JArray(value);
    }
    Json::Json(const JObject &&value)
    {
        type = JsonType::Object;
        jobject = new JObject(value);
    }
    Json::Json(const JString &&value)
    {
        type = JsonType::String;
        jstring = new JString(value);
    }
    Json::Json(const JNumber &&value)
    {
        type = JsonType::Number;
        jnumber = new JNumber(value);
    }
    Json::Json(const JBool &&value)
    {
        type = JsonType::Boolean;
        jbool = new JBool(value);
    }
    Json::Json::~Json()
    {
        switch (type)
        {
        case JsonType::Array:
            if (jarray)
                delete jarray;
            break;
        case JsonType::Object:
            if (jobject)
                delete jobject;
            break;
        case JsonType::Number:
            if (jnumber)
                delete jnumber;
            break;
        case JsonType::Boolean:
            if (jbool)
                delete jbool;
            break;
        case JsonType::String:
            if (jstring)
                delete jstring;
            break;
        }
        return;
    }

    Json &Json::operator[](const std::string &name)
    {
        return (*jobject)[name];
    }

    JBool &Json::asbool() const
    {
        if (type != JsonType::Boolean)
            throw ValueTypeError();
        return *jbool;
    }
    JNumber &Json::asnumber() const
    {
        if (type != JsonType::Number)
            throw ValueTypeError();
        return *jnumber;
    }
    JString &Json::asstring() const
    {
        if (type != JsonType::String)
            throw ValueTypeError();
        return *jstring;
    }
    JArray &Json::asarray() const
    {
        if (type != JsonType::Array)
            throw ValueTypeError();
        return *jarray;
    }
    JObject &Json::asobject() const
    {
        if (type != JsonType::Object)
            throw ValueTypeError();
        return *jobject;
    }
    const Json Json::parse(const std::string &raw_json)
    {
        Json res;
        auto it = raw_json.begin();

        std::cout << "char read:\t" << *it << std::endl;
        switch (*it)
        {
        case '{':
        {
            res = Json(JsonType::Object);
            ++it;
            while (*it != '}')
            {
                std::string key, value_cache;
                Json value;
                // 先找到第一个key的"
                std::cout << "object char read:\t"<<*it << std::endl;

                while (*it != '\"')
                    it++;

                while (*it != '\"')
                    key += *it++;

                ++it; // 跳过冒号

                while (*it++ != ',')
                    value_cache += *it;

                std::cout << "value cache\t" << value_cache << std::endl;
                value = parse(value_cache);
                std::cout << "processed\t" << value.stringrify() << std::endl;
                res[key] = value;

                ++it;
            }
            break;
        }
        case '\"':
        {
            std::string cache;
            ++it;
            while (*it != '\"')
                cache += *it++;

            res = JString(cache);
            break;
        }
        case 't':
            res = JBool(true);
            it += 4;
            break;
        case 'f':
            res = JBool(false);
            it += 5;
            break;
        case ',':
            ++it;
            break;
        case '0' ... '9':
        {
            std::string cache;
            while (*it++ != ',')
                cache += *it;
            res = JNumber(atof(cache.c_str()));
            break;
        }
        default:
            ++it;
            break;
        }
        return res;
    }
    const std::string Json::stringrify() const
    {
        std::stringstream ss;
        switch (type)
        {
        case JsonType::Array:
        {
            ss << '[';
            for (const auto &jv : *jarray)
                ss << jv.stringrify() << ",";
            std::string str = ss.str();
            str = str.assign(str.begin(), str.end() - 1) + "]";
            return str;
        }
        case JsonType::Boolean:
            return ((*jbool) ? "true" : "false");
        case JsonType::Null:
            return "null";
        case JsonType::Number:
            return std::to_string(*jnumber);
        case JsonType::Object:
        {
            ss << '{' << '\n';
            for (const auto &[k, v] : *jobject)
            {
                ss << "\t\"" << k << "\":" << v.stringrify() << ",\n";
            }
            std::string str = ss.str();
            str = str.assign(str.begin(), str.end() - 2) + "\n}";
            return str;
        }
        case JsonType::String:
            ss << '\"' << *jstring << "\"";
            return ss.str();

        default:
            return ss.str();
        }
    }
}