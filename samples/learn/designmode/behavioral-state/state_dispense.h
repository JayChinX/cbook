#ifndef __STATE_DISPENSE_H__
#define __STATE_DISPENSE_H__

#include "state.h"

class RaffleActivity;
class DispenseState : public State {
  public:
    DispenseState(RaffleActivity *activity);
    void deductMeney() override;
    bool raffle() override;
    // 发放奖品
    void dispensePrize() override;

  private:
    RaffleActivity *activity;
};


#endif // __STATE_DISPENSE_H__