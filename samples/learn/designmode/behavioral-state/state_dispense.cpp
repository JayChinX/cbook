#include "state_dispense.h"
#include "raffle.h"
#include <iostream>
#include <ostream>

DispenseState::DispenseState(RaffleActivity *activity) {
    this->activity = activity;
}

void DispenseState::deductMeney() {
    std::cout << "不能扣除积分" << std::endl;
}

bool DispenseState::raffle() {
    std::cout << "不能抽奖了" << std::endl;
    return false;
}

void DispenseState::dispensePrize() {
    if (activity->getCount() > 0) {
        std::cout << "送出奖品" << std::endl;
        activity->setState(activity->getNoRaffleState());
    } else {
        std::cout << "很遗憾，奖品发完了" << std::endl;
        // 奖品发完了，后面不能抽奖了
        activity->setState(activity->getDispenseOutState());
    }
}
