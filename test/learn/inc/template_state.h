
#ifndef __TEMPLATE_STATE__H__
#define __TEMPLATE_STATE__H__

template<typename T>
class State {
  public:
    T getIdentify() const;
    void setIdentify(const T &);

  protected:
    T identify;
};
#include "template_state.inc"

#endif // __TEMPLATE_STATE_H__