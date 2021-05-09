#pragma once

#include "pin.h"
/**
 * @class LED
 * Our LED pin, controls the light level using `step()` and `off()`
 */
class LED : OutputPin {
public:
  LED(int pin,bool reverse);
  /**
   * Step the light to the next level, uses the time based `stepValue()` method
   */ 
  void step();
  /**
   * Turns off the led
   */
  void off();
  
private:
    /**
     * A simple 4 second time based cycle, feel free to replace with your own effect
     * 0 -> scale up from LED_LOW_LIGHT-255
     * 1 -> sleep keep value
     * 2 -> scale down to LED_LOW_LIGHT
     * 3 -> sleep for 1 sec
    */
    static int stepValue();
    bool _isOff;
    int _level;
    bool _isReverse;
};
