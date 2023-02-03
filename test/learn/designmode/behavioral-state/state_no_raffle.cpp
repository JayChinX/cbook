#include "state_no_raffle.h"
#include "raffle.h"
#include <iostream>

NoRaffleState::NoRaffleState(RaffleActivity *activity) {
    this->activity = activity;
}

void NoRaffleState::deductMeney() {
    std::cout << "扣除50积分，可以抽奖了" << std::endl;
    activity->setState(activity->getCanRaffleState());
}

bool NoRaffleState::raffle() {
    std::cout << "扣了积分才能抽奖" << std::endl;
    return false;
}

void NoRaffleState::dispensePrize() {
    std::cout << "不能发奖品" << std::endl;
}
