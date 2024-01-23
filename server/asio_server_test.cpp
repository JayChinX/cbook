#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>

using namespace boost::asio;
using namespace boost::system;
using namespace boost::placeholders;

boost::asio::io_service service;

size_t read_complete(char *buff, const error_code &err, size_t bytes)
{
    if (err)
        return 0;
    bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
    // 我们一个一个读取直到读到回车，不缓存
    return found ? 0 : 1;
}
void handle_connections()
{
    // 端点
    ip::tcp::endpoint ep(ip::tcp::v4(), 8001);

    // 接收器，初始化协议和端口号，等待接入连接
    ip::tcp::acceptor acceptor(service, ep);
    // 写入缓冲区
    char buff[1024];
    while (true) {
        ip::tcp::socket sock(service);
        // 阻塞等待接入
        acceptor.accept(sock);
        // 有接入，同步读取
        int bytes = read(sock, buffer(buff), boost::bind(read_complete, buff, _1, _2));

        // 接收的消息
        std::string msg(buff, bytes);
        // 返回字段
        std::string call("Server Call");

        // 同步写入消息
        sock.write_some(buffer(call.append(" ").append(msg)));
        // 关闭
        sock.close();
    }
}
int main(int argc, char *argv[])
{
    handle_connections();
}