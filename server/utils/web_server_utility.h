#ifndef __WEB_SERVER_UTILITY_H__
#define __WEB_SERVER_UTILITY_H__

// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// Added for the default_resource example
#include <boost/filesystem.hpp>

#include <algorithm>
#include <fstream>
#include <vector>

// web_server
#include "client_http.hpp"
#include "server_http.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

#endif  // __WEB_SERVER_UTILITY_H__