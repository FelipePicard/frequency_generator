# frequency_generator

Square wave frequency generator using Teensy 3.2's analogWriteFrequency functionality to allow us to create waves in the megahertz range.
It was also a good project to create a simple GUI using an OLED screen and a rotary encoder to interface with it.
Lastly, to avoid burning the Teensy's frequency generating PWM pin, an optocupler was added to the circuit to isolate the processor from the circuit it is feeding the frequency to.
