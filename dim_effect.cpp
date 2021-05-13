#include "dim_effect.h"
#include <Arduino.h>

DimEffect::DimEffect(LED** led,int count):Effect(led,count){
  
}

/**
 * A simple 4 second time based cycle, feel free to replace with your own effect
 * 0 -> scale up from LED_LOW_LIGHT-255
 * 1 -> sleep keep value
 * 2 -> scale down to LED_LOW_LIGHT
 * 3 -> sleep for 1 sec
*/
void DimEffect::step(LED& led,int index){
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
  index % 2 == 0 ?  level : 255 - level;
  led.set(level);
}
