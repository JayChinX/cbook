#ifndef __RAFFLE_H__
#define __RAFFLE_H__

#include "./state.h"
#include "state_can_raffle.h"
#include "state_dispense.h"
#include "state_dispense_out.h"
#include "state_no_raffle.h"

class RaffleActivity {
  public:
    RaffleActivity(int count);

    State *getState() const;

    void setState(State *const state);

    int getCount();

    void setCount(const int count);

    State *getNoRaffleState();

    void setNoRaffleState(State *const noRaffleState);

    State *getCanRaffleState() const;

    void setCanRaffleState(State *const canRaffleState);

    State *getDispenseState() const;

    void setDispenseState(State *dispenseState);

    State *getDispenseOutState() const;

    void setDispenseOutState(State *dispenseOutState);

    // 扣分
    void deductMoney();

    // 抽奖
    void raffle();

  private:
    State *state = nullptr, *noRaffleState = new NoRaffleState(this),
          *canRaffleState = new CanRaffleState(this),
          *dispenseState = new DispenseState(this),
          *dispenseOutState = new DispenseOutState(this);
    // 奖品数
    int count;
};

#endif // __RAFFLE_H__