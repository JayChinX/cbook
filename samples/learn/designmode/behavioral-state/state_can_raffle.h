#ifndef __STATE_CAN_RAFFLE_H__
#define __STATE_CAN_RAFFLE_H__

#include "state.h"
class RaffleActivity;

class CanRaffleState : public State {
  public:
    CanRaffleState(RaffleActivity *activity);
    // 已经扣除积分了，不能在扣了
    void deductMeney() override;

    bool raffle() override;

    void dispensePrize() override;

  private:
    RaffleActivity *activity;
};
#endif // __STATE_CAN_RAFFLE_H__