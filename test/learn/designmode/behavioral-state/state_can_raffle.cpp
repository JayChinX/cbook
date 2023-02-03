#include "state_can_raffle.h"
#include "raffle.h"
#include <iostream>

CanRaffleState::CanRaffleState(RaffleActivity *activity) {
    srand(time(NULL));
    this->activity = activity;
}

void CanRaffleState::deductMeney() {
    std::cout << "已经扣除积分了" << std::endl;
}

bool CanRaffleState::raffle() {
    std::cout << "正在抽奖" << std::endl;
    int result = rand() % 10;
    if (0 == result) {
        // 设置为发奖品状态
        std::cout << "🎉🎉恭喜你中奖了🎉🎉" << std::endl;
        activity->setState(activity->getDispenseState());
        return true;
    } else {
        std::cout << "很遗憾没有抽中奖品" << std::endl;
        // 设置为不能抽奖状态
        activity->setState(activity->getNoRaffleState());
        return false;
    }
}

void CanRaffleState::dispensePrize() {
    std::cout << "没中奖，不能发放奖品" << std::endl;
}
