
#pragma once 
#include <Arduino.h>

#define DEBUG

template<typename T>
void println(T t){
#ifdef DEBUG
  Serial.println(t);
#endif
}

template<typename T>
void print(T t){
#ifdef DEBUG
  Serial.print(t);
#endif

}
