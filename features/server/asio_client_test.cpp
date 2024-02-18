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

// 读取完成后的处理句柄
size_t read_complete(char *buf, const error_code &err, size_t bytes)
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
    // 创建 socket 对象
    ip::tcp::socket socket(service);
    // socket 同步连接端点
    socket.connect(ep);
    // 同步发送缓冲区数据，阻塞等待发送完成
    socket.write_some(buffer(msg));

    char buf[1024];
    // 同步读取，写入 buf 缓冲区
    // boost::bind 函数适配器，函数绑定
    int bytes = read(socket, buffer(buf), boost::bind(read_complete, buf, _1, _2));

    // 拷贝构造，复制 buf 的前 bytes - 1 个字符，去掉最后一个 '\n' 换行符
    std::string copy(buf, bytes - 1);

    // 提取原来的 msg，去掉最后一个 '\n' 换行符
    msg = msg.substr(0, msg.size() - 1);

    // 接收的 buf 与 原来的 msg 是否相同
    std::cout << "Server echo our -> " << msg << ", call echo: " << copy << std::endl;

    // 关闭连接
    socket.close();
}

int main(int argc, char **argv)
{
    std::cout << __FILE__ << std::endl;
    // 端点
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);

    std::string messages[] = {"John says hi", "so does James"};

    // 线程组
    boost::thread_group threads;

    for (const std::string &message : messages) {
        threads.create_thread(boost::bind(sync_echo, ep, message));
        boost::this_thread::sleep(boost::posix_time::millisec(100));
    }

    threads.join_all();
    return 0;
}
