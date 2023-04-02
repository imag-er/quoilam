#pragma once
#include <vector>
#include <map>
#include <string>
namespace quoilam
{

    enum class JsonValueType
    {
        Null = 0,
        Boolean,
        Number,
        String,
        Array,
        Object
    };
    class JsonValue;
    using JNumber = double;
    using JBool = bool;
    using JArray = std::vector<JsonValue>;
    using JObject = std::map<std::string, JsonValue>;
    using JString = std::string;
    class JsonValue
    {
    public:
        JsonValue();
        JsonValue(JsonValueType value_type);

        JsonValue &operator[](const std::string &name);

        JsonValue &operator=(const JArray &value);
        JsonValue &operator=(const JObject &value);
        JsonValue &operator=(const JString &value);
        JsonValue &operator=(const JNumber &value);
        JsonValue &operator=(const JBool &value);

        JBool &asbool();
        JNumber &asnumber();
        JString &asstring();
        JArray &asarray();

        class ValueTypeError : public std::runtime_error
        {
        public:
            ValueTypeError(const std::string &msg = "value type error") : std::runtime_error(msg){};
        };

        ~JsonValue();

        const std::string stringrify() const;

    private:
        JsonValueType type;

        union
        {
            JBool *jbool;
            JNumber *jnumber;
            JString *jstring;
            JArray *jarray;
            JObject *jobject = nullptr;
        };
    };

} // namespace quoilam
