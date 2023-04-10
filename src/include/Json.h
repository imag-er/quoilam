#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>
namespace quoilam
{

    enum class JsonType
    {
        Null = 0,
        Boolean,
        Number,
        String,
        Array,
        Object
    };
    class Json;
    using JNumber = double;
    using JBool = bool;
    using JArray = std::vector<Json>;
    using JObject = std::map<std::string, Json>;
    using JString = std::string;
    class Json
    {
    public:
        Json(const Json &value);  // 拷贝构造
        Json(const Json &&value); // 移动构造

        Json &operator=(const Json &value); // 赋值构造

        Json(JsonType value_type = JsonType::Null);

        Json(const JArray &&value);
        Json(const JObject &&value);
        Json(const JString &&value);
        Json(const JNumber &&value);
        Json(const JBool &&value);

        Json &operator[](const std::string &name);

        Json &operator=(const JArray &value);
        Json &operator=(const JObject &value);
        Json &operator=(const JString &value);
        Json &operator=(const JNumber &value);
        Json &operator=(const JBool &value);

        JBool &asbool() const;
        JNumber &asnumber() const;
        JString &asstring() const;
        JArray &asarray() const;
        JObject &asobject() const;

        const JBool getbool() const;
        const JNumber getnumber() const;
        const JString getstring() const;
        const JArray getarray() const;
        const JObject getobject() const;

        class ValueTypeError : public std::runtime_error
        {
        public:
            ValueTypeError(const std::string &msg = "value type error") : std::runtime_error(msg){};
        };

        ~Json();

        const std::string stringrify() const;
        const Json copy() const;
        const Json parse(const std::string &raw_json);

        JsonType type;

    private:
        union
        {
            JBool *jbool;
            JNumber *jnumber;
            JString *jstring;
            JArray *jarray;
            JObject *jobject;
        };
    };

} // namespace quoilam
