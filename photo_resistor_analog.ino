#include "pin.h"
#include "led.h"
#include "ldr.h"
#include "push_button.h"
#include "dim_effect.h"
/**
 * D3,D5 are PWM pins in the Nano, Uno and Mega 2560, so same code works for all three boards
 * Feel free to change for your board
*/
const int LED_PINS[] = { 3,5 };
const int BUTTON_PIN = 6;
const int LED_COUNT = sizeof(LED_PINS) / sizeof(int);
/*
 * We'll read the input from this pin
 */
const int LDR_PIN = A0;
const int POT_PIN = A1;

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
void loop(){ 
  enum WasBright {
    YES,
    NO,
    UNINITIALIZED
  };
  LDR ldr(LDR_PIN,POT_PIN);
  PushButton button(BUTTON_PIN);
  LED** leds = reinterpret_cast<LED**>(malloc(sizeof(LED*)*LED_COUNT));
  WasBright was_bright = UNINITIALIZED;
  { // scope for temp vars
    int i=0;
    for (auto pin : LED_PINS){
      leds[i++] = new LED(pin);
    }
  }
  button.buttonStateChanged = [](bool state){
    Serial.print("State changed to ");
    Serial.println(state ? "on" : "off");
  };
  const size_t effect_count = 1;
  Effect** effects = reinterpret_cast<Effect**>(malloc(sizeof(Effect*)*effect_count));
  int effect_index = 0;
  while (true){
    button.step();
    // Is it bright outside?
    if (ldr.isBright()){
      // Only print this when actually switching state
      if (was_bright != YES){
        was_bright = YES;
        Serial.println("Bright! turning lights off");
      }
      // Turn it off, there's light outside
      for (int i=0;i<LED_COUNT;++i) leds[i]->set(0);
    } else { // Dark!
      // Only print this when actually switching state
      if (was_bright == YES){
        was_bright = NO;
        Serial.println("Bright! turning lights on");
      }
      // Cycle the LED to the next value
      effects[effect_index % effect_count]->step();
    }
  }
  
}
