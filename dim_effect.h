#pragma once

#include "effect.h"

class DimEffect : public Effect {
public:
  DimEffect(LED** led,int count);
protected:
  virtual void step(LED& led,int index);
};
