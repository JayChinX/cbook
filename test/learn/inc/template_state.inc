#include "template_state.h"


template<typename T>
void State<T>::setIdentify(const T &id) {
    this->identify = id;
}

template<typename T>
T State<T>::getIdentify() const {
    return this->identify;
}