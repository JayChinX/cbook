#include <boost/filesystem/fstream.hpp>
#include <utility>
#include <boost/config/pragma_message.hpp>
#include <boost/describe.hpp>
#include "api/model/Person.h"
#include "jsons.h"

using namespace std;
// Added for the json-example:
using namespace boost::property_tree;

void jsons(HttpServer &server)
{
    // POST-example for the path /json, responds firstName+" "+lastName from the posted json
    // Responds with an appropriate error message if the posted json is not valid, or if firstName or lastName is
    // missing Example posted json:
    // {
    //   "firstName": "John",
    //   "lastName": "Smith",
    //   "age": 25
    // }
    server.resource["^/json$"]["GET"] = [](shared_ptr<HttpServer::Response> response,
                                           shared_ptr<HttpServer::Request> request) {
        try {
            // ptree pt;

            // json 解析
            // read_json(request->content, pt);
            ptree pt_json;

            // json 文件读取
            auto path = boost::filesystem::path(filename()).parent_path().generic_string();
            cout << "json01 path -> " << path << std::endl;

            read_json(path + "/../assets/json01.json", pt_json);

            // 读取字段
            string test = pt_json.get<string>("data.test");
            cout << "json01 -> " << test << std::endl;

            // 写入 stringstream 中，转为 json string
            stringstream s;
            write_json(s, pt_json, false);

            // auto name = pt.get<string>("firstName") + " " + pt.get<string>("lastName");

            auto res = s.str();

            printf("rep %s\n", res.c_str());

            response->write(res);
        } catch (const exception &e) {
            response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
        }

        // Alternatively, using a convenience function:
        // try {
        //     ptree pt;
        //     read_json(request->content, pt);

        //     auto name=pt.get<string>("firstName")+" "+pt.get<string>("lastName");
        //     response->write(name);
        // // *response << "HTTP/1.1 200 OK\r\n"
        //           << "Content-Length: " << res.length() << "\r\n\r\n"
        //           << res;
        // }
        // catch(const exception &e) {
        //     response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
        //  // *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" <<
        // e.what();
        // }
    };
}

void json_obj(HttpServer &server)
{
    server.resource["^/jsonobj$"]["GET"] = [](shared_ptr<HttpServer::Response> response,
                                              shared_ptr<HttpServer::Request> request) {
        try {
            // ptree pt;

            // json 解析
            // read_json(request->content, pt);

            // json 文件读取
            auto path = boost::filesystem::path(filename()).parent_path().generic_string();
            cout << "json01 path -> " << path << std::endl;

            // 文件读取
            boost::filesystem::ifstream file(path + "/../assets/json01.json");
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            std::cout << "File content: " << content << std::endl;

            // 读取字段

            auto data = boost::json::value_to<Person>(boost::json::parse(content));

            // auto name = pt.get<string>("firstName") + " " + pt.get<string>("lastName");

            // auto res = s.str();

            printf("data name  %s\n", data.data.name.c_str());

            response->write(boost::json::serialize(boost::json::value_from(data)));
        } catch (const exception &e) {
            response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
        }

        // Alternatively, using a convenience function:
        // try {
        //     ptree pt;
        //     read_json(request->content, pt);

        //     auto name=pt.get<string>("firstName")+" "+pt.get<string>("lastName");
        //     response->write(name);
        // // *response << "HTTP/1.1 200 OK\r\n"
        //           << "Content-Length: " << res.length() << "\r\n\r\n"
        //           << res;
        // }
        // catch(const exception &e) {
        //     response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
        //  // *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" <<
        // e.what();
        // }
    };
}
