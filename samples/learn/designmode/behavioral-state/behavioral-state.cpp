
// 状态模式
#include "raffle.h"
#include "state_can_raffle.h"
#include <cstring>
#include <iostream>

int main() {
    RaffleActivity *activity = new RaffleActivity(30);
    for (int i = 0; i < 50; ++i) {
        std::cout << "第" << i << "次抽奖" << std::endl;
        activity->deductMoney();
        activity->raffle();
        std::cout << std::endl;
    }
    return 0;
}
