/**
 * D11 is a PWM pin in the Nano, Uno and Mega 2560, so same code works for all three boards
 * Feel free to change for your board
*/
const int LED_PIN = 11;
/**
 * We'll read the input from this pin
 */
const int LDR_PIN = A0;
/**
 * Experiment for the best value for you, the value range is 0..1023 (10bit unsigned), where 0 is total darkness. 
 */
const int LIGHT_THRESHOLD = 450;
/**
 * Minimal low light value, valid range should be 0..255, where 0 means turn off the led, and 255 means keep it fully lit
 */
const int LED_LOW_LIGHT=4;

/**
 * @class Pin
 * Basic pin, encapsulates a pin number
 */
class Pin {
public:
  Pin(int pin):_pin(pin){}
protected:
  int _pin;
};

/**
 * @class InputPin
 * A pin that allows reading input values
 */
class InputPin : Pin {
public:
  InputPin(int pin):Pin(pin){
    pinMode(_pin,INPUT);
  }
  /**
   * @return The pin analog value (unsigned 10 bits by default, meaning 0..1023)
   */
  int analogRead() const{
    return ::analogRead(_pin);
  }
};

/**
 * @class OutputPin
 * A pin that allows writing values
 */
class OutputPin : Pin {
public:
  OutputPin(int pin):Pin(pin){
    pinMode(_pin,OUTPUT);
  }
  /**
   * @param level By default, this value is an unsigned 8 bit value
   */ 
  void analogWrite(int level) const{
    ::analogWrite(_pin,level);
  }
  /**
   * @param on A simple wrapper to `digitalWrite`, translates `true` to `HIGH` and `false` to `LOW`
   */
  void digitalWrite(bool on) const{
    ::digitalWrite(_pin,on ? HIGH : LOW);
  }
};

/**
 * @class LED
 * Our LED pin, controls the light level using `step()` and `off()`
 */
class LED : OutputPin {
public:
  LED(int pin):
    OutputPin(pin),
    _isOff(true),
    _level(0){}
  /**
   * Step the light to the next level, uses the time based `stepValue()` method
   */ 
  void step(){
    int level = LED::stepValue();
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
  void off(){
    if (!_isOff){
      _isOff = true;
      digitalWrite(false);
    }
  }
  
  private:
    /**
     * A simple 4 second time based cycle, feel free to replace with your own effect
     * 0 -> scale up from LED_LOW_LIGHT-255
     * 1 -> sleep keep value
     * 2 -> scale down to LED_LOW_LIGHT
     * 3 -> sleep for 1 sec
    */
    static int stepValue(){
      unsigned long now = millis();
      int level;
      // Split the resolution to seconds (/1000) and then, mod by 4, so we get nice 4 second intervals, in a predictable, time based manner (look mom! no state!)
      switch ((now / 1000) % 4){
        case 0:
          level = (int)(((float)(now % 1000)) / 1000.0 * (255-LED_LOW_LIGHT)) + LED_LOW_LIGHT;
          break;
        case 1:
          level = 255;
          break;
        case 2:
          level = 255 - (int)(((float)(now % 1000)) / 1000.0 * (255-LED_LOW_LIGHT));
          break;
        case 3:
        default: // this (`default:`) only supresses the warning about the uninitialized variable, which is bogus, of course.
          level = LED_LOW_LIGHT;
          break;
      }
      return level;
    }
    bool _isOff;
    int _level;
};

/**
 * @class LDR
 * Our LDR (light dependent resistor) class
 * Used to determine the light level outside
 */
class LDR : InputPin{
 public:
  LDR(int pin):
  InputPin(pin){}
  /**
   * @return True if bright, false if dark.
   * @see LIGHT_THRESHOLD
   */
  bool isBright() const {
    return analogRead() > LIGHT_THRESHOLD;
  }
};

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
  WasBright was_bright = UNINITIALIZED;
  LED led(LED_PIN);
  LDR ldr(LDR_PIN);
  while (true){
    // Is it bright outside?
    if (ldr.isBright()){
      // Only print this when actually switching state
      if (was_bright != YES){
        was_bright = YES;
        Serial.println("Bright! turning lights off");
      }
      // Turn it off, there's light outside
      led.off();
    } else { // Dark!
      // Only print this when actually switching state
      if (was_bright == YES){
        was_bright = NO;
        Serial.println("Bright! turning lights on");
      }
      // Cycle the LED to the next value
      led.step();
    }
  }
  
}
