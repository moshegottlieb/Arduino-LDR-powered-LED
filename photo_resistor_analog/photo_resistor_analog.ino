#include <ArduinoShark.h> // Get it from https://github.com/moshegottlieb/arduinoshark/
#include "dim_effect.h"
/**
 * D3,D5 are PWM pins in the Nano, Uno and Mega 2560, so same code works for all three boards
 * Feel free to change for your board
*/
const int LED_PINS[] = { 5,6 };
const int BUTTON_PIN = 3;
const int LED_COUNT = sizeof(LED_PINS) / sizeof(int);
/*
 * We'll read the input from this pin
 */
const int POT_PIN = A5;

/**
 * Initialize, no idea why arduino calls `setup()` and `loop()` and not just a single entry point
 */
void setup() {
  Serial.begin(9600);
  Serial.println("Initialization completed");
}

/**
 * We're going to use our own loop instead of relying on the board/framework to call `loop()` repeatedly because:
 * 1. It makes more sense, sorry arduino guys - not sure what you were thinking about
 * 2. We can instantiate our classes on the stack, and every programmer knows the stack is their friend
 * 3. Easier to read, don't you think?
 * 4. While not very significant, this is more performant, no needless stack pushing and popping
 */

int effect_index = 0; // cannot use std::funcion, so I can't capture anything on the lambda
void loop(){ 
  PushButton button(BUTTON_PIN);
  LED** leds = reinterpret_cast<LED**>(malloc(sizeof(LED*)*LED_COUNT));
  { // scope for temp vars
    int i=0;
    for (auto pin : LED_PINS){
      leds[i++] = new LED(pin);
    }
  }
  const size_t effect_count = 3;
  Effect** effects = reinterpret_cast<Effect**>(malloc(sizeof(Effect*)*effect_count));
  effects[0] = new DimEffect(leds,LED_COUNT,12);
  effects[1] = new DimEffect(leds,LED_COUNT,8);
  effects[2] = new DimEffect(leds,LED_COUNT,4);
  button.buttonStateChanged = [](bool state){
    Serial.print("State changed to ");
    Serial.println(state ? "on" : "off");
    if (state) ++effect_index;
  };

  Serial.println("Starting loop");
  while (true){
    //button.step();
    // Cycle the LED to the next value
    effects[effect_index % effect_count]->step();
  }
  
}
