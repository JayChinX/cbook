#include "works.h"
void works(HttpServer &server)
{
    // GET-example simulating heavy work in a separate thread
    server.resource["^/work$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response,
                                           std::shared_ptr<HttpServer::Request> /*request*/) {
        std::thread work_thread([response] {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            response->write("Work done");
        });
        work_thread.detach();
    };
}
