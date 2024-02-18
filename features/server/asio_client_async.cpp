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

class talk_to_svr : public boost::enable_shared_from_this<talk_to_svr>, boost::noncopyable {
    using self_type = talk_to_svr;

    talk_to_svr(const std::string &message) : sock_(service), started_(true), message_(message) {}

    void start(const ip::tcp::endpoint &ep)
    {
        // 异步方式连接地址，连接成功执行 on_content
        sock_.async_connect(ep, MEM_FN1(on_content, _1));
    }

public:
    using ptr = boost::shared_ptr<talk_to_svr>;  // 共享指针

    // 静态方法启动
    static ptr start(const ip::tcp::endpoint &ep, const std::string &message)
    {
        // 智能指针
        ptr new_(new talk_to_svr(message));
        new_->start(ep);
        return new_;
    }

    void stop()
    {
        if (!started_)
            return;
        started_ = false;
        sock_.close();
    }
    bool started()
    {
        return started_;
    }

    void on_content(const error_code &err)
    {
        if (!err) {
            // 连接成功。写入数据
            do_write(message_ + '\n');
        } else {
            stop();
        }
    }

    void do_read()
    {
        // 异步读取数据到缓冲区
        async_read(sock_, buffer(read_buffer_), MEM_FN2(on_read, _1, _2));
    }

    void do_write(const std::string &msg)
    {
        if (!started()) {
            return;
        }
        // 将要发送的数据写入缓冲区
        std::copy(msg.begin(), msg.end(), write_buffer_);

        // 异步发送，发送缓冲区数据
        sock_.async_write_some(buffer(write_buffer_, msg.size()), MEM_FN2(on_write, _1, _2));
    }

    void on_read(const error_code &err, size_t bytes)
    {
        // if (!err) {
        // 读取完成
        // 拷贝构造，复制 buf 的前 bytes - 1 个字符，去掉最后一个 '\n' 换行符
        std::string copy(read_buffer_, bytes - 1);

        // 接收的 buf 与 原来的 msg 是否相同
        std::cout << "Server echo our -> " << message_ << ", call echo: " << copy << std::endl;
        // }
        stop();
    }

    void on_write(const error_code &err, size_t bytes)
    {
        do_read();
    }

private:
    ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
    std::string message_;
};

int main(int argc, char **argv)
{
    std::cout << __FILE__ << std::endl;
    // 端点
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);

    std::string messages[] = {"John says hi", "so does James"};

    for (const std::string &message : messages) {
        talk_to_svr::start(ep, message);
        boost::this_thread::sleep(boost::posix_time::millisec(100));
    }

    // 异步操作，主要保持 service 一直运行
    service.run();

    return 0;
}
