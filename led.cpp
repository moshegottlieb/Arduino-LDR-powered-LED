#include "led.h"
#include <Arduino.h>

LED::LED(int pin):
    OutputPin(pin),
    _level(-1){

  }
  
void LED::set(int level){
  if (level != _level){
    _level = level;
    analogWrite(_level);
  }
}
