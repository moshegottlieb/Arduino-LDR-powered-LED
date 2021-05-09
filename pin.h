#pragma once


/**
 * @class Pin
 * Basic pin, encapsulates a pin number
 */
class Pin {
public:
  Pin(int pin);
protected:
  int _pin;
};


/**
 * @class InputPin
 * A pin that allows reading input values
 */
class InputPin : public Pin {
public:
  InputPin(int pin);
  /**
   * @return The pin analog value (unsigned 10 bits by default, meaning 0..1023)
   */
  int analogRead() const;
  bool digitalRead() const;
};

/**
 * @class OutputPin
 * A pin that allows writing values
 */
class OutputPin : public Pin {
public:
  OutputPin(int pin);
  /**
   * @param level By default, this value is an unsigned 8 bit value
   */ 
  void analogWrite(int level) const;
  /**
   * @param on A simple wrapper to `digitalWrite`, translates `true` to `HIGH` and `false` to `LOW`
   */
  void digitalWrite(bool on) const;
};
