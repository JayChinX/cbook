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
    server.resource["^/json$"]["POST"] = [](shared_ptr<HttpServer::Response> response,
                                            shared_ptr<HttpServer::Request> request) {
        try {
            ptree pt;

            // TODO: json
            read_json(request->content, pt);

            auto name = pt.get<string>("firstName") + " " + pt.get<string>("lastName");

            *response << "HTTP/1.1 200 OK\r\n"
                      << "Content-Length: " << name.length() << "\r\n\r\n"
                      << name;
        } catch (const exception &e) {
            *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }

        // Alternatively, using a convenience function:
        // try {
        //     ptree pt;
        //     read_json(request->content, pt);

        //     auto name=pt.get<string>("firstName")+" "+pt.get<string>("lastName");
        //     response->write(name);
        // }
        // catch(const exception &e) {
        //     response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
        // }
    };
}
