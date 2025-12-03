#include <gtest/gtest.h>

#include <iostream>
#include <ostream>

#include "../../lib/json11/json11.hpp"

TEST(Json11Test, case1)
{
    std::string test_json =
        "{\"name\":\"Awesome 4K\",\"resolutions\":[{\"width\":1280,\"height\":720}, {\"width\":1920,\"height\":1080}, "
        "{\"width\":3840,\"height\":2160}]}";
    std::string err;
    const auto json = json11::Json::parse(test_json, err);

    if (!json.is_null() && err.empty()) {
        std::cout << "name: " << json["name"].string_value() << std::endl;
        std::cout << "resolutions: " << json["resolutions"].array_items().size() << std::endl;

        for (auto &item : json["resolutions"].array_items()) {
            std::cout << "     - " << item.dump() << std::endl;
        }
    }

    const json11::Json json1 = json11::Json::object {
        {"name", "q"}, {"list", json11::Json::array {1, 2, 3}}, {"age", true}, {"color", nullptr}};
    std::cout << "json: " << json1.dump() << std::endl;
}
