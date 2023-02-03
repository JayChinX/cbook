#ifndef __STATE_NO_RAFFLE_H__
#define __STATE_NO_RAFFLE_H__


#include "state.h"

class RaffleActivity;

class NoRaffleState : public State {
  public:
    NoRaffleState(RaffleActivity *activity);
    void deductMeney() override;
    bool raffle() override;
    // 发放奖品
    void dispensePrize() override;

  private:
    RaffleActivity *activity;
};


#endif // __STATE_NO_RAFFLE_H__