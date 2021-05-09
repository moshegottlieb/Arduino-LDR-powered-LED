#pragma once

#include "pin.h"

/**
 * @class LDR
 * Our LDR (light dependent resistor) class
 * Used to determine the light level outside
 */
class LDR : InputPin{
 public:
  LDR(int pin,int pot);
  /**
   * @return True if bright, false if dark.
   * @see LIGHT_THRESHOLD
   */
  bool isBright() const;
private:
  InputPin _pot;
};
