# ECE3400 Fall 2017
## Lab 1 TA Reference

1.  The TAs should start every lab with a brief introduction to what the students are supposed to do. Make sure everyone knows where the lab-instructions are located. You can also start by briefly introducing basic lab equipment and describe the components the students will use. Keep your intros brief so that everyone can get onto their work. 
2.  If the same question appears many times during a session, it is a good idea to ask everyone to pause their work, and discuss the questions with all four teams at the same time. 
3.  Near the end of the lab, when the first teams have started wrapping up, you should again address all the teams, and remind them to write up everything on their webpage, and what is needed to complete milestone 1. 

### Introduction
This lab will go over the basics of using the Arduino microcontroller, as well as some of its applications. Here are some talking points for the start of the lab, feel free to use as many or few of these points as you want.
* **Basic lab equipment:** Talk about power supplies, oscilloscopes, digital multimeters, and function generators. Go over how use the ones in the lab.
* **What is a microcontroller?** Explain how microcontrollers are small computers used for embedded systems. Explain that they are programmed and have peripherals that allow it communicate with the outside world via inputs and outputs, such as digital input and output, PWM, serial communication, analog input, etc.
* **Uses for microcontrollers:** Explain some basic uses of microcontrollers in embedded systems. If you've ever worked with microcontrollers, explain what you used them for. Otherwise discuss their use in a field such as automotive, aerospace, consumer electronics, research, medical, hobbyist, etc.
* **Limits of Arduino microcontroller:** Explain basic limits of microcontrollers, specifically the Arduino's ATMega328p. Maximum voltage (5V without regulator, 12V with regulator), maximum current (40mA) per pin, clock speed (16 MHz @ 5V, 8MHz @ 3.3V). Explain why 330&Omega; resistors are recommended on I/O pins and how these resistors effect the I/O characteristics of the Arduino.
* **How LEDs work in a circuit:** Explain that an LED is a Light Emitting **Diode** and functions as a diode in a circuit. Discuss what a diode is and how it functions in a circuit. Explain why an in series resistor is always needed when using an LED.
* **Analog vs. Digital signals:** Discuss the difference between analog and digital signals. Explain common uses for both kinds of signals, such as digital communication between devices or reading from analog sensors.
* **Serial communication:** Explain how the Arduino communicates with the computer through a Serial communication protocol. Explain what Baudrate is. Discuss different communication protocols (I2C, SPI, parallel communications).
* **What is PWM and why is it useful?** Explain how PWM works and its characteristics, such as frequency and duty cycle. Discuss uses of PWM signals for controlling motors, servos, LED control, etc.
* **Using servos/motors with microcontrollers:** Discuss challenges of using high power devices (servos/motors) with microcontrollers. Explain importance of isolating servos/motors from sensitive electronics using transistors, optoisolators, etc.

### Team materials

#### Ardunio getting started
* 2 Arduinos
* 2 USB A/B cables
* 2 Breadboards
* 10k&Omega; potentiometer
* ~20k&Omega; - 1k&Omega; for voltage divider
* ~330&Omega; - 500&Omega; resistor for LED
* Parallax continuous rotation servo

The following parts are needed to build a full robot. All of these parts are not necessary to Lab 1; therefore, you should let the students find these as needed.

#### Robot parts

* Baseplate
* 2 servo mounts
* 2 Parallax continuous rotation servos
* Ball bearing mount
* Ball bearing
* 3mm screws
* 3mm nuts
* Battery-options: 9V battery, 9V battery clip-barrel jack adapter, 6V AA battery pack, 4 AA batteries

#### Line sensor parts
* 4 line sensor mounts
* 4 line sensors
* 2 Op-Amps
* Male headers
* Assorted resistors

#### Wall sensor parts
* 3 wall sensor mounts
* 3 long/short range wall sensors
* 3 IR cables

#### Useful references
- [Arduino pinout](http://foros.giltesa.com/otros/arduino/fc/docs/pinout/uno.jpg)
- [Arduino datasheet](https://www.farnell.com/datasheets/1682209.pdf)
- [ATMega328p datasheet](http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf)
- [Arduino IDE reference](https://www.arduino.cc/en/Reference/HomePage)
- [Servo library reference](https://playground.arduino.cc/ComponentLib/Servo)
- [Common Arduino problems](https://www.arduino.cc/en/Guide/Troubleshooting)
- [LM358 Op-Amp datasheet](http://www.ti.com/lit/ds/symlink/lm358.pdf	)
- [LF353 Op-Amp datasheet](http://www.ti.com/lit/ds/symlink/lf353-n.pdf)

### Lab extras
Towards the final robot and milestone 1!

#### Line Sensors
The line sensors work as grayscale sensors, and there datasheet can be found [here](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/QRE1113.pdf). Since analog pins on the Arduino are limited, it is advisable for the students to convert the grayscale sensor's analog signal into a digital signal using a [Schmitt Trigger](http://howtomechatronics.com/how-it-works/electrical-engineering/schmitt-trigger/). Before making the Schmitt Trigger, students are advised to experiment with the line sensors and electrical tape to find the cut-off value(s) that work best for line detection. The students may also use a multiplexer in order to read from all 4 line sensors using only one analog pin, but this means they will have to order their own multiplexer from Digikey or Sparkfun. They could also read from the line sensors using one analog pin each, but since the wall detection sensors also output an analog signal, this is not advised. These are just a few of the ways line detection can be done, and students are free to explore other options.

#### Wall Detection
There are 2 wall detection sensors, one long range and the other short range. The datasheet for the long range sensor can be found [here](http://www.jameco.com/Jameco/Products/ProdDS/2136454.pdf). The datasheet for the short range sensor can be found [here](https://www.pololu.com/file/0J713/GP2Y0A41SK0F.pdf). The most important figure on the datasheet is the distance-measuring-characteristics graph, which maps output to distance. Be aware, that at very short distances the output can be the same as at longer distances. The minimum trustable value is at ~3cm for the short distance sensor and ~15cm for the long distance sensor. It is up to the students to decide how they will deal with this issue, but since the maze is relatively small and the robots only need to sense objects in a relatively short distance, it may be helpful for the students to measure distance only using above the minimum value of the sensor.
