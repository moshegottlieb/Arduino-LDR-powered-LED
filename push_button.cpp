#include "push_button.h"

PushButton::PushButton(int pin):InputPin(pin),buttonStateChanged(nullptr),_state(-1){
}

void PushButton::step(){
  bool state = digitalRead();
  if (state != this->_state){
    this->_state = state;
    if (buttonStateChanged){
      buttonStateChanged(state);
    }
  }
}