#ifndef __RAPIDJSONHELPER_H__
#define __RAPIDJSONHELPER_H__

#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// 序列化
// 开始 序列化，顺序
#define RapidjsonWriteBegin(writer) \
    {                               \
        writer.StartObject();
// 结束 对象序列化
#define RapidjsonWriteEnd() \
    writer.EndObject();     \
    }
// 基础类型序列化 先读取为 string，再将转换为 相应的json
#define RapidjsonWriteString(XXX) \
    writer.Key(#XXX);             \
    writer.String(XXX.data());
#define RapidjsonWriteChar(XXX) \
    writer.Key(#XXX);           \
    writer.String(XXX, strlen(XXX));
#define RapidjsonWriteInt(XXX) \
    writer.Key(#XXX);          \
    writer.Int(XXX);
#define RapidjsonWriteInt64(XXX) \
    writer.Key(#XXX);            \
    writer.Int64(XXX);
#define RapidjsonWriteUInt(XXX) \
    writer.Key(#XXX);           \
    writer.UInt(XXX);
#define RapidjsonWriteUint64(XXX) \
    writer.Key(#XXX);             \
    writer.Uint64(XXX);
#define RapidjsonWriteDouble(XXX) \
    writer.Key(#XXX);             \
    writer.Double(XXX);
// 类对象序列化
#define RapidjsonWriteClass(XXX) \
    writer.Key(#XXX);            \
    ((JsonBase *)(&XXX))->ToWrite(writer);
// array 类型
#define RapidjsonWriteArray(XXX)                                                \
    writer.Key(#XXX);                                                           \
    RapidJsonHelper::JsonArray<typename decltype(XXX)::value_type> values(XXX); \
    values.ToWrite(writer)


// 反序列化
// 开始 遍历 value
#define RapidjsonParseBegin(val) \
    for (Value::ConstMemberIterator itr = val.MemberBegin(); itr != val.MemberEnd(); ++itr) {
// 结束
#define RapidjsonParseEnd() }
// 基础类型的反序列化 先读取为 string，判断 是否 存在，再读取相应类型
#define RapidjsonParseToString(XXX)               \
    if (strcmp(itr->name.GetString(), #XXX) == 0) \
        XXX = itr->value.GetString();
#define RapidjsonParseToInt(XXX)                  \
    if (strcmp(itr->name.GetString(), #XXX) == 0) \
        XXX = itr->value.GetInt();
#define RapidjsonParseToInt64(XXX)                \
    if (strcmp(itr->name.GetString(), #XXX) == 0) \
        XXX = itr->value.GetInt64();
#define RapidjsonParseToUInt(XXX)                 \
    if (strcmp(itr->name.GetString(), #XXX) == 0) \
        XXX = itr->value.GetUint();
#define RapidjsonParseToUint64(XXX)               \
    if (strcmp(itr->name.GetString(), #XXX) == 0) \
        XXX = itr->value.GetUint64();
#define RapidjsonParseToDouble(XXX)               \
    if (strcmp(itr->name.GetString(), #XXX) == 0) \
        XXX = itr->value.GetDouble();
#define RapidjsonParseToClass(XXX)                \
    if (strcmp(itr->name.GetString(), #XXX) == 0) \
        ((JsonBase *)(&XXX))->ParseJson(itr->value);
#define RapidjsonParseToChar(XXX)                   \
    if (strcmp(itr->name.GetString(), #XXX) == 0) { \
        int size = ARRAY_SIZE(XXX);                 \
        const char *s = itr->value.GetString();     \
        int len = strlen(s);                        \
        strncpy(XXX, s, std::min(size, len));       \
    }
// array 类型
#define RapidjsonParseToArray(XXX)                                              \
    if (strcmp(itr->name.GetString(), #XXX) == 0) {                             \
        const Value &v = itr->value;                                            \
        RapidJsonHelper::JsonArray<typename decltype(XXX)::value_type> ja(XXX); \
        ja.ParseJson(v);                                                        \
        XXX = ja.arr;                                                           \
    }

namespace RapidJsonHelper {
using namespace rapidjson;

class JsonBase {
public:
    JsonBase() {}
    ~JsonBase() {}

    // 序列化
    std::string ToJson()
    {
        StringBuffer s;
        Writer<StringBuffer> writer(s);
        this->ToWrite(writer);
        return s.GetString();
    }
    // 反序列化
    static void FromJson(JsonBase *p, const std::string &json)
    {
        Document document;
        document.Parse(json.data());
        const Value &val = document;
        p->ParseJson(val);
    }

protected:
    // 范型模版函数，处理 array 的 item
    template <typename T>
    static void ToWriteEvery(Writer<StringBuffer> &writer, T &val)
    {
        JsonBase *p = &val;
        p->ToWrite(writer);
    }
    // 特化 int32
    static void ToWriteEvery(Writer<StringBuffer> &writer, int32_t &val)
    {
        writer.Int(val);
    }
    static void ToWriteEvery(Writer<StringBuffer> &writer, int64_t &val)
    {
        writer.Int64(val);
    }
    static void ToWriteEvery(Writer<StringBuffer> &writer, uint32_t &val)
    {
        writer.Uint(val);
    }
    static void ToWriteEvery(Writer<StringBuffer> &writer, uint64_t &val)
    {
        writer.Uint64(val);
    }
    static void ToWriteEvery(Writer<StringBuffer> &writer, double &val)
    {
        writer.Double(val);
    }
    static void ToWriteEvery(Writer<StringBuffer> &writer, bool &val)
    {
        writer.Bool(val);
    }
    static void ToWriteEvery(Writer<StringBuffer> &writer, std::string &val)
    {
        writer.String(val.data());
    }
    static void ToWriteEvery(Writer<StringBuffer> &writer, char *val)
    {
        writer.String(val, strlen(val));
    }

    // 范型模版函数
    template <typename T>
    static void ToParseEvery(const Value &val, T &t)
    {
        JsonBase *p = &t;
        p->ParseJson(val);
    }

    // 特化
    static void ToParseEvery(const Value &val, int32_t &t)
    {
        t = val.GetInt();
    }
    static void ToParseEvery(const Value &val, int64_t &t)
    {
        t = val.GetInt64();
    }
    static void ToParseEvery(const Value &val, uint32_t &t)
    {
        t = val.GetUint();
    }
    static void ToParseEvery(const Value &val, uint64_t &t)
    {
        t = val.GetUint64();
    }
    static void ToParseEvery(const Value &val, double &t)
    {
        t = val.GetDouble();
    }
    static void ToParseEvery(const Value &val, bool &t)
    {
        t = val.GetBool();
    }
    static void ToParseEvery(const Value &val, std::string &t)
    {
        t = val.GetString();
    }
    static void ToParseEvery(const Value &val, char t[])
    {
        int size = ARRAY_SIZE(t);
        const char *s = val.GetString();
        int len = strlen(s);
        strncpy(t, s, std::min(size, len));
    }

public:
    virtual void ToWrite(Writer<StringBuffer> &writer) {}
    virtual void ParseJson(const Value &val) {}
};

// 特化 array 类型
template <typename T>
class JsonArray : public JsonBase {
public:
    std::list<T> arr;
    JsonArray() {}
    JsonArray(std::list<T> arr) : arr(arr) {}
    ~JsonArray() {}

public:
    virtual void ToWrite(Writer<StringBuffer> &writer)
    {
        writer.StartArray();
        for (auto ent : arr) {
            ToWriteEvery(writer, ent);
        }
        writer.EndArray();
    }

    virtual void ParseJson(const Value &val)
    {
        SizeType len = val.Size();
        for (size_t i = 0; i < len; i++) {
            const Value &f = val[i];
            T t;
            ToParseEvery(f, t);
            arr.push_back(t);
        }
    }
};

}  // namespace RapidJsonHelper

#endif  // __RAPIDJSONHELPER_H__