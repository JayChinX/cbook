#include <future>

#include "client_http.hpp"
#include "server_http.hpp"

#include "web/info.h"
#include "web/index.h"

#include "api/jsons.h"
#include "api/match.h"
#include "api/strings.h"
#include "api/login.h"
#include "api/works.h"

#include "utils/web_server_utility.h"

#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif

using namespace std;
// Added for the json-example:
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

void router_api(HttpServer &server)
{
    login(server);
    strings(server);
    jsons(server);
    info(server);
    match(server);
    works(server);
    index(server);

    server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
        // Handle errors here
        // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
    };
}

int main()
{
    // HTTP-server at port 8080 using 1 thread
    // Unless you do more heavy non-threaded processing in the resources,
    // 1 thread is usually faster than several threads
    HttpServer server;
    server.config.port = 8080;

    router_api(server);

    // Start server and receive assigned port when server is listening for requests
    promise<unsigned short> server_port;
    thread server_thread([&server, &server_port]() {
        // Start server
        server.start([&server_port](unsigned short port) {
            //
            server_port.set_value(port);
        });
    });
    // server_port.get_future().get() 阻塞
    cout << "Server listening on port " << server_port.get_future().get() << endl << endl;

    server_thread.join();

    // Client examples
    // string json_string = "{\"firstName\": \"John\",\"lastName\": \"Smith\",\"age\": 25}";

    // // Synchronous request examples
    // {
    //     HttpClient client("localhost:8080");
    //     try {
    //         cout << "Example GET request to http://localhost:8080/match/123" << endl;
    //         auto r1 = client.request("GET", "/match/123");
    //         cout << "Response content: " << r1->content.rdbuf()
    //              << endl  // Alternatively, use the convenience function r1->content.string()
    //              << endl;

    //         cout << "Example POST request to http://localhost:8080/string" << endl;
    //         auto r2 = client.request("POST", "/string", json_string);
    //         cout << "Response content: " << r2->content.rdbuf() << endl << endl;
    //     } catch (const SimpleWeb::system_error &e) {
    //         cerr << "Client request error: " << e.what() << endl;
    //     }
    // }

    // // Asynchronous request example
    // {
    //     HttpClient client("localhost:8080");
    //     cout << "Example POST request to http://localhost:8080/json" << endl;
    //     client.request("POST", "/json", json_string,
    //                    [](shared_ptr<HttpClient::Response> response, const SimpleWeb::error_code &ec) {
    //                        if (!ec)
    //                            cout << "Response content: " << response->content.rdbuf() << endl;
    //                    });
    //     client.io_service->run();
    // }
}
