#include "Person.h"

Person::Person(Name data, int b) : data(data), b(b) {}

Person::Name::Name(const std::string &name) : name(name) {}

Person::Name tag_invoke(boost::json::value_to_tag<Person::Name>, boost::json::value const &jv)
{
    auto &jo = jv.as_object();
    return {boost::json::value_to<std::string>(jo.at("name"))};
}

void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Person::Name const &c)
{
    auto &jo = jv.emplace_object();
    jo["name"] = c.name;
}

Person tag_invoke(boost::json::value_to_tag<Person>, boost::json::value const &jv)
{
    auto &jo = jv.as_object();

    return {boost::json::value_to<Person::Name>(jo.at("data")), 1};
}

void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Person const &c)
{
    auto &jo = jv.emplace_object();
    jo["data"] = boost::json::value_from(c.data);
    jo["b"] = c.b;
}
