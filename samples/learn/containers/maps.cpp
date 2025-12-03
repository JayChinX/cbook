
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <ostream>
#include <utility>
int main(int argc, char **argv) {
    std::map<const char *, const char *> mp;
    std::map<const char *, const char *>::iterator iter;

    const char key[3][20] = {"img", "system", "ip"};
    const char value[3][20] = {"./a.img", "mac", "193.68.6.3"};

    //插入
    // 1. 插入 make_pair
    for (int i = 0; i < 2; ++i) { mp.insert(std::make_pair(key[i], value[i])); }
    // 2. 插入 pair
    mp.insert(std::pair<const char *, const char *>(key[2], value[2]));
    // 3。数组插入
    mp["addr"] = "中国";

    //查询
    // 1. 迭代器
    for (iter = mp.begin(); iter != mp.end(); ++iter) {
        std::cout << iter->first << "\t" << iter->second << std::endl;
    }

    char key1[20];
    std::cout << "请输入按key查找：";
    std::cin.getline(key1, 20);
    //
    for (iter = mp.begin(); iter != mp.end(); ++iter) {
        if (strcmp(iter->first, key1) == 0) {
            std::cout << iter->first << "找到了，对应值为：" << iter->second
                      << std::endl;
        }
    }
    // std::cout << mp.at(key1) << std::endl;

    // 删除
    iter = mp.find("addr");
    if (iter != mp.end()) {
        std::cout << iter->first << "按照key查找出来了！"
                  << "对应的value为：" << iter->second << std::endl;
        std::cout << "开始删除元素！" << std::endl;
        mp.erase(iter);
    }

    //第二种方式删除
    //按照key删除元素
    char drop_key[20];
    //按照value删除元素
    char drop_value[20];
    std::cout << "请输入按key删除：";
    std::cin.getline(drop_key, 20);
    std::cout << "请输入按value删除：";
    std::cin.getline(drop_value, 20);
    for (iter = mp.begin(); iter != mp.end(); iter++) {
        if (strcmp(iter->first, drop_key) == 0) {
            std::cout << iter->first << "按照key查找出来了！"
                      << "对应的value为：" << iter->second << std::endl;
            std::cout << "开始删除元素！" << std::endl;
            mp.erase(iter);
        }
        if (strcmp(iter->second, drop_value) == 0) {
            std::cout << iter->second << "value查找出来了！"
                      << "对应的key为：" << iter->first << std::endl;
            std::cout << "开始删除元素！" << std::endl;
            mp.erase(iter);
        }
    }
    std::cout << "------删除元素以后--------\n";
    //循环取出元素
    for (iter = mp.begin(); iter != mp.end(); iter++) {
        std::cout << iter->first << "\t" << iter->second << std::endl;
    }

    system("pause");
    return 0;
}
