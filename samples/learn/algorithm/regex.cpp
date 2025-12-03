#include <iostream>
#include <ostream>
#include <string>
#include <regex>

int main(int argc, char **argv)
{
    // 匹配判断
    std::string str = "simple";
    std::regex rePattern("simpl.");

    std::cout << std::boolalpha << std::regex_match(str, rePattern) << std::endl;

    std::regex rePattern1("simp..");

    std::cout << std::boolalpha << std::regex_match(str, rePattern1) << std::endl;

    // 匹配具体结果，并存储
    std::smatch match;
    str = "foot.txt";
    std::regex rePattern2("(foot)\\.txt");
    std::cout << std::boolalpha << std::regex_match(str, match, rePattern2) << std::endl;
    // 打印结果
    std::cout << match[0] << ":" << match[1] << std::endl;

    std::regex rePattern3("(....)\\.txt");
    std::cout << std::boolalpha << std::regex_match(str, match, rePattern3) << std::endl;

    str = "ft.txt";
    std::regex rePattern4("fo*t\\.txt");
    std::cout << std::boolalpha << std::regex_match(str, match, rePattern4) << std::endl;

    // regex search
    str = "Color is #ffAB11";
    std::regex rePattern5("#([a-f]{2})");
    std::cout << std::boolalpha << std::regex_search(str, match, rePattern5) << std::endl;

    system("pause");
    return 0;
}
