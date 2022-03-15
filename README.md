# Arduino LDR powered LED

A simple LDR controlled LED that cycles the LED power using a simple time based step function.  
It also uses simple  [charlieplexing](https://en.wikipedia.org/wiki/Charlieplexing) to alternately light two leds using 2 wires, and that's because I use it to light my balcony lights.    
Here's a photo showing my poor engineering skills and total inability to solder, using an [arduino nano compatible board](https://amzn.to/3vG7pHR) (3 for 13€) but hey, it's a weather proof 3€ smart home appliance :-)   
I've also added a potentiometer, so it would be eaiser to adjust the light sensitivity.  

Wrapped it in a little box:
![3 euro smart home](https://github.com/moshegottlieb/Arduino-LDR-powered-LED/blob/main/box.jpg?raw=true)

Let there be light!
![LED string](https://github.com/moshegottlieb/Arduino-LDR-powered-LED/blob/main/light.jpg?raw=true)


Here's the diagram:
![Diagram](https://github.com/moshegottlieb/Arduino-LDR-powered-LED/blob/main/layout.png?raw=true)

Here's the [circuit on tinkercad](https://www.tinkercad.com/things/e26Up9S0e0M-ldr-controlled-balcony-lights-with-a-potentiometer)
