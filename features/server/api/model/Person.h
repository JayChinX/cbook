#ifndef __PERSON_H__
#define __PERSON_H__

#include "utils/web_server_utility.h"
#include "JsonBase.h"

#include <string>

class Name : public JsonBase {
public:
    std::string name;
    Name();
    Name(const std::string &name);
    ~Name() {}

    void ParseJson(const std::string &json) override;
    std::string toWrite() override;
};

class Person : public JsonBase {
public:
    Name name;
    int age;
    Person();
    Person(Name name, int age = 1);
    ~Person() {}

    void ParseJson(const std::string &json) override;
    std::string toWrite() override;
};

// 定义反序列化特化函数

// Person::Name tag_invoke(boost::json::value_to_tag<Person::Name>, boost::json::value const &jv);
// void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Person::Name const &c);

// Person tag_invoke(boost::json::value_to_tag<Person>, boost::json::value const &jv);
// void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Person const &c);
#endif  // __PERSON_H__