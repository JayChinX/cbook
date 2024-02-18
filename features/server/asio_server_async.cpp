#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <utility>

using namespace boost::asio;
using namespace boost::system;
using namespace boost::placeholders;

#define MEM_FN(x) boost::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x, y) boost::bind(&self_type::x, shared_from_this(), y)
#define MEM_FN2(x, y, z) boost::bind(&self_type::x, shared_from_this(), y, z)

io_service service;

class talk_to_client : public std::enable_shared_from_this<talk_to_client>, boost::noncopyable {
    using self_type = talk_to_client;

    talk_to_client() : sock_(service), started_(false) {}

public:
    // 智能指针
    using ptr = std::shared_ptr<talk_to_client>;

    static ptr new_()
    {
        ptr new_(new talk_to_client);
        return new_;
    }

    void start()
    {
        started_ = true;
        do_read();
    }

    void stop()
    {
        if (!started_) {
            return;
        }
        started_ = false;
        sock_.close();
    }

    ip::tcp::socket &sock()
    {
        return sock_;
    }

    void do_read()
    {
        // 异步读取数据到缓冲区
        async_read(sock_, buffer(read_buffer_), MEM_FN2(on_read, _1, _2));
    }

    void do_write(const std::string &msg)
    {
        // 将要发送的数据写入缓冲区
        std::copy(msg.begin(), msg.end(), write_buffer_);

        // 异步发送，发送缓冲区数据
        sock_.async_write_some(buffer(write_buffer_, msg.size()), MEM_FN2(on_write_complete, _1, _2));
    }
    void on_read(const error_code &err, size_t bytes)
    {
        // if (!err) {
        std::string msg(read_buffer_, bytes);
        do_write(msg + '\n');
        // }
    }

    void on_write(const error_code &err, size_t bytes)
    {
        do_read();
    }

    void on_write_complete(const error_code &err, size_t bytes)
    {
        stop();
    }

private:
    ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
};

ip::tcp::endpoint ep(ip::tcp::v4(), 8001);
ip::tcp::acceptor acceptor(service, ep);
void handle_accept(talk_to_client::ptr client, const error_code &err)
{
    client->start();
    talk_to_client::ptr new_client = talk_to_client::new_();
    acceptor.async_accept(new_client->sock(), boost::bind(handle_accept, client, _1));
}

int main(int argc, char **argv)
{
    talk_to_client::ptr client = talk_to_client::new_();

    acceptor.async_accept(client->sock(), boost::bind(handle_accept, client, _1));
    service.run();
    return 0;
}
