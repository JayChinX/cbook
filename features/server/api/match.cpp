#include "match.h"

void match(HttpServer &server)
{
    // GET-example for the path /match/[number], responds with the matched string in path (number)
    // For instance a request GET /match/123 will receive: 123
    server.resource["^/match/([0-9]+)$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response,
                                                     std::shared_ptr<HttpServer::Request> request) {
        response->write(request->path_match[1].str());
    };
}