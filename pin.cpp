#include "pin.h"
#include <Arduino.h>

Pin::Pin(int pin):_pin(pin){

}

InputPin::InputPin(int pin):Pin(pin){
    pinMode(_pin,INPUT);
}

int InputPin::analogRead() const{
    return ::analogRead(_pin);
}
bool InputPin::digitalRead() const{
    return ::digitalRead(_pin) == HIGH;
}


  OutputPin::OutputPin(int pin):Pin(pin){
    pinMode(_pin,OUTPUT);
  }
  
  void OutputPin::analogWrite(int level) const{
    ::analogWrite(_pin,level);
  }
  
  void OutputPin::digitalWrite(bool on) const{
    ::digitalWrite(_pin,on ? HIGH : LOW);
  }
