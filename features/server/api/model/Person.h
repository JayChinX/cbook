#ifndef __PERSON_H__
#define __PERSON_H__

#include "utils/web_server_utility.h"

#include <string>

class Person {
public:
    class Name {
    public:
        std::string name;
        Name(const std::string &name);
    };
    Name data;
    int b;
    Person(Name data, int b = 1);
};

// 定义反序列化特化函数

Person::Name tag_invoke(boost::json::value_to_tag<Person::Name>, boost::json::value const &jv);
void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Person::Name const &c);

Person tag_invoke(boost::json::value_to_tag<Person>, boost::json::value const &jv);
void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Person const &c);
#endif  // __PERSON_H__