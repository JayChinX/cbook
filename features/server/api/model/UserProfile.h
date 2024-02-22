#ifndef __USERPROFILE_H__
#define __USERPROFILE_H__

#include "utils/web_server_utility.h"
#include "RapidjsonHelper.h"

#include <string>

using namespace rapidjson;

class UserName : public RapidJsonHelper::JsonBase {
public:
    std::string name;
    UserName();
    UserName(const std::string &name);
    ~UserName() {}

    void ToWrite(Writer<StringBuffer> &writer) override
    {
        RapidjsonWriteBegin(writer);
        RapidjsonWriteString(name);
        RapidjsonWriteEnd();
    }

    void ParseJson(const Value &val) override
    {
        RapidjsonParseBegin(val);
        RapidjsonParseToString(name);
        RapidjsonParseEnd();
    }
};

class UserProfile : public RapidJsonHelper::JsonBase {
public:
    UserName name;
    std::string nick;
    char book[100];
    int age;
    double money;
    std::list<UserName> formers;
    UserProfile();
    UserProfile(UserName name, int age = 0, double money = 0);
    ~UserProfile() {}

    void ToWrite(rapidjson::Writer<rapidjson::StringBuffer> &writer) override
    {
        RapidjsonWriteBegin(writer);
        RapidjsonWriteString(nick);
        RapidjsonWriteChar(book);
        RapidjsonWriteInt(age);
        RapidjsonWriteDouble(money);
        RapidjsonWriteClass(name);
        RapidjsonWriteArray(formers);
        RapidjsonWriteEnd();
    }

    void ParseJson(const Value &val) override
    {
        RapidjsonParseBegin(val);
        RapidjsonParseToString(nick);
        RapidjsonParseToChar(book);
        RapidjsonParseToInt(age);
        RapidjsonParseToDouble(money);
        RapidjsonParseToClass(name);
        RapidjsonParseToArray(formers);
        RapidjsonParseEnd();
    }
};
#endif  // __USERPROFILE_H__