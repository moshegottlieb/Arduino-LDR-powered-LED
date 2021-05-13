#pragma once

#include "led.h"

class Effect {
public:
  Effect(LED** led,int count);
  virtual void step();
protected:
  virtual void step(LED& led,int index) = 0;
protected:
  LED** _led;
  int _count;
};
