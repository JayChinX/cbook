#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>

using namespace boost::asio;
using namespace boost::system;
using namespace boost::placeholders;

io_service service;

size_t read_complate(char *buf, const error_code &err, size_t bytes)
{
    if (err) {
        return 0;
    }

    bool found = std::find(buf, buf + bytes, '\n') < buf + bytes;
    return found ? 0 : 1;
}

void sync_echo(ip::tcp::endpoint ep, std::string msg)
{
    msg += "\n";
    ip::tcp::socket socket(service);
    socket.connect(ep);
    socket.write_some(buffer(msg));

    char buf[1024];
    int bytes = read(socket, buffer(buf), boost::bind(read_complate, buf, _1, _2));

    std::string copy(buf, bytes - 1);
    msg = msg.substr(0, msg.size() - 1);
    std::cout << "Server echod our -> " << msg << ": " << (copy == msg ? "Ok" : "Fail") << ", call: " << copy
              << std::endl;
    socket.close();
}

int main(int argc, char **argv)
{
    std::cout << __FILE__ << std::endl;
    // 端点
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);

    std::string messages[] = {"John says hi", "so does James"};
    boost::thread_group threads;

    for (const std::string &message : messages) {
        threads.create_thread(boost::bind(sync_echo, ep, message));
        boost::this_thread::sleep(boost::posix_time::millisec(100));
    }

    threads.join_all();
    return 0;
}
