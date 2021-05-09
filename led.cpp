#include "led.h"
#include <Arduino.h>

LED::LED(int pin,bool reverse):
    OutputPin(pin),
    _isOff(true),
    _level(0),
    _isReverse(reverse){

  }
  
void LED::step(){
  int level = LED::stepValue();
  // Reverse the value? good for charlieplexing
  if (_isReverse) level = 255 - level;
  /**
    * I've no idea what is the cost of `analogWrite` (performance wise), but I know I only want to call it when I need to, hence the `_isOff` and `_level` check 
    */
  if (_isOff || level != _level){
    _level = level;
    _isOff = false;
    analogWrite(_level);
  }
}
/**
* Turns off the led
*/
void LED::off(){
  if (!_isOff){
    _isOff = true;
    digitalWrite(false);
  }
}

int LED::stepValue(){
  unsigned long now = millis();
  int level;
  // Split the resolution to seconds (/1000) and then, mod by 4, so we get nice 4 second intervals, in a predictable, time based manner (look mom! no state!)
  switch ((now / 1000) % 4){
    case 0:
      level = (int)(((float)(now % 1000)) / 1000.0 * 255);
      break;
    case 1:
      level = 255;
      break;
    case 2:
      level = 255 - (int)(((float)(now % 1000)) / 1000.0 * 255);
      break;
    case 3:
    default: // this (`default:`) only supresses the warning about the uninitialized variable, which is bogus, of course.
      level = 0;
      break;
  }
  return level;
}
