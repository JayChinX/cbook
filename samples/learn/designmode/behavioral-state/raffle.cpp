
#include "./raffle.h"

RaffleActivity::RaffleActivity(int count) {
    // 初始化为不能抽奖状态
    this->state = getNoRaffleState();
    // 初始化奖品数量
    this->count = count;
}

State *RaffleActivity::getState() const {
    return state;
}

void RaffleActivity::setState(State *const state) {
    this->state = state;
}

int RaffleActivity::getCount() {
    return count--;
}

void RaffleActivity::setCount(const int count) {
    this->count = count;
}

State *RaffleActivity::getNoRaffleState() {
    return noRaffleState;
}

void RaffleActivity::setNoRaffleState(State *const noRaffleState) {
    this->noRaffleState = noRaffleState;
}

State *RaffleActivity::getCanRaffleState() const {
    return canRaffleState;
}

void RaffleActivity::setCanRaffleState(State *const canRaffleState) {
    this->canRaffleState = canRaffleState;
}

State *RaffleActivity::getDispenseState() const {
    return dispenseState;
}

void RaffleActivity::setDispenseState(State *dispenseState) {
    this->dispenseState = dispenseState;
}

State *RaffleActivity::getDispenseOutState() const {
    return dispenseOutState;
}

void RaffleActivity::setDispenseOutState(State *dispenseOutState) {
    this->dispenseOutState = dispenseOutState;
}

void RaffleActivity::deductMoney() {
    state->deductMeney();
}

void RaffleActivity::raffle() {
    // 是否抽中
    if (state->raffle()) {
        // 发奖品
        state->dispensePrize();
    }
}
