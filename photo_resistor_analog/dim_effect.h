#pragma once

#include "effect.h"

class DimEffect : public Effect {
public:
  DimEffect(LED** led,int count,int cycle = 4);
protected:
  virtual void step(LED& led,int index);
private:
  int _cycle;
};
