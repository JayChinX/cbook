#include "state_dispense_out.h"
#include "raffle.h"
#include <iostream>
#include <ostream>

DispenseOutState::DispenseOutState(RaffleActivity *activity) {
    this->activity = activity;
}

void DispenseOutState::deductMeney() {
    std::cout << "奖品已经发完了，请下次再参加" << std::endl;
}

bool DispenseOutState::raffle() {
    std::cout << "奖品已经发完了，请下次再参加" << std::endl;
    return false;
}

void DispenseOutState::dispensePrize() {
    std::cout << "奖品已经发完了，请下次再参加" << std::endl;
}
