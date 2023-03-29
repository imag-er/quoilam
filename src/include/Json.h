#pragma once
#include <vector>
#include <map>
#include <string>
namespace quoilam
{
    enum class JsonValueType
    {
        Null,
        Boolean,
        Number,
        String,
        Array,
        Object
    };
    struct JsonValue
    {
        JsonValueType type;
        union
        {
            bool jbool;
            double jnumber;
            std::string *jstring;
            std::vector<JsonValue> *jarray;
            std::map<std::string, JsonValue> *jobject;
        };

        JsonValue();
        JsonValue(bool value);
        JsonValue(double value);
        JsonValue(const std::string &value);
        JsonValue(const std::vector<JsonValue> &value);
        JsonValue(const std::map<std::string, JsonValue> &value);

        JsonValue &operator[](const std::string &name);

        JsonValue& operator=(bool value);
        JsonValue& operator=(double value);
        JsonValue& operator=(const std::string &value);
        JsonValue& operator=(const std::vector<JsonValue> &value);
        JsonValue& operator=(const std::map<std::string, JsonValue> &value);

        ~JsonValue();
    };
} // namespace quoilam
