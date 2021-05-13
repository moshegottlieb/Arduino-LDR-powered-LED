#include "effect.h"

Effect::Effect(LED** led,int count):_led(led),_count(count){
  
}

void Effect::step(){
  for (int i=0;i<_count;++i) step(*(_led[i]),i);
}
