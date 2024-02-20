#include <string>

#include "utils/web_server_utility.h"

class JsonBase {
public:
    JsonBase() {}
    ~JsonBase() {}

    virtual void ParseJson(const std::string &json) {}
    virtual std::string toWrite() {};

    // <boost/json.hpp> 实现序列化
    std::string ToJson()
    {
        return this->toWrite();
    }

    // <boost/json.hpp> 实现反序列化
    static void FromJson(JsonBase *p, const std::string &json)
    {
        p->ParseJson(json);
    }
};