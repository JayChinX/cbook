#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <string>

boost::asio::io_service service;

void sync_echo(boost::asio::ip::tcp::endpoint ep, std::string msg)
{
    msg += "\n";
    boost::asio::ip::tcp::socket socket(service);
    socket.connect(ep);
}

int main(int argc, char **argv)
{
    // 端点
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 8001);

    std::string messages[] = {"John says hi", "so does James"};
    boost::thread_group threads;

    for (const std::string &message : messages) {
        threads.create_thread(boost::bind(sync_echo, ep, message));
        boost::this_thread::sleep(boost::posix_time::millisec(100));
    }

    threads.join_all();
    return 0;
}
