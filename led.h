#pragma once

#include "pin.h"
/**
 * @class LED
 * Our LED pin, controls the light level using `step()` and `off()`
 */
class LED : OutputPin {
public:
  LED(int pin);
  /**
   * Set the led level (0-255)
   */ 
  void set(int level);
  
private:
    static int stepValue();
    bool _isOff;
    int _level;
    bool _isReverse;
};
