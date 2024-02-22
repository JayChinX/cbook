#include "Person.h"

Person::Person() : name(Name()), age(0) {}

Person::Person(Name data, int age) : name(data), age(age) {}

// 定义序列化和反序列化特化函数
void Person::ParseJson(const std::string &json)
{
    auto data = boost::json::value_to<Person>(boost::json::parse(json));
    *this = data;
}

std::string Person::toWrite()
{
    return boost::json::serialize(boost::json::value_from(*this));
}

Person tag_invoke(boost::json::value_to_tag<Person>, boost::json::value const &jv)
{
    auto &jo = jv.as_object();
    return {boost::json::value_to<Name>(jo.at("name")),
            jo.if_contains("age") ? static_cast<int>(jo.at("age").as_int64()) : 0};
}

void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Person const &c)
{
    auto &jo = jv.emplace_object();
    jo["name"] = boost::json::value_from(c.name);
    jo["age"] = c.age;
}

// Name
Name::Name() {}

Name::Name(const std::string &name) : name(name) {}

// 定义序列化和反序列化特化函数
void Name::ParseJson(const std::string &json)
{
    auto data = boost::json::value_to<Name>(boost::json::parse(json));
    *this = data;
}

std::string Name::toWrite()
{
    return boost::json::serialize(boost::json::value_from(*this));
}

Name tag_invoke(boost::json::value_to_tag<Name>, boost::json::value const &jv)
{
    auto &jo = jv.as_object();
    return {boost::json::value_to<std::string>(jo.at("name"))};
}

void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Name const &c)
{
    auto &jo = jv.emplace_object();
    jo["name"] = c.name;
}
