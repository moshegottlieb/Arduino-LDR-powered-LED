#include "ldr.h"

LDR::LDR(int pin,int pot):
  InputPin(pin),_pot(pot){

}
bool LDR::isBright() const {
  //Serial.print("LDR ");
  int value = analogRead();
  //Serial.println(value);
  return value > _pot.analogRead();
}
