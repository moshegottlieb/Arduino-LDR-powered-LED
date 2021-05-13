#include "dim_effect.h"
#include <Arduino.h>
#define __ASSERT_USE_STDERR
#include <assert.h>

DimEffect::DimEffect(LED** led,int count,int cycle):Effect(led,count),_cycle(cycle){
  assert(cycle % 4 == 0); // cycle must be divisible by 4
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
  int k = 1000 * (_cycle / 4);
  int sec = (now / k) % 4;
  Serial.println(sec);
  
  switch (sec){
    case 0:
      level = (int)(((float)(now % k)) / (float)k * 255);
      break;
    case 1:
      level = 255;
      break;
    case 2:
      level = 255 - (int)(((float)(now % k)) / (float)k * 255);
      break;
    case 3:
    default: // this (`default:`) only supresses the warning about the uninitialized variable, which is bogus, of course.
      level = 0;
      break;
  }
  level = index % 2 == 0 ?  level : 255 - level;
  led.set(level);
}
