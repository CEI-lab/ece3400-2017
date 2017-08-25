# ECE3400 Fall 2017
## Introduction to Arduinos

*By Kirstin Petersen, Aug 25th 2017.*

This tutorial gives a brief introduction to Arduino Unos. (Basically everything we went over in Lecture 2, but more legible).

### Arduino IDE

Arduino IDE is currently the most popular popular tool for programming Arduino boards. IDE stands for Integrated DEvelopment Environment. The interface is meant to enable people with very little experience to program exciting robots/devices. This also means that it integrates a large number of libraries to make sure everything works. 

* Open Arduino IDE
* Make sure that the IDE knows the correct board you are working with (> Tools > Board > Arduino/Genuino Uno)
* It will automatically open the last sketch you had opened, or if this is your first time it will open a blank sketch that looks like this:
```C
void setup() {
  //Put your setup code here (initialize input/output pins, analog pins, ADC, timers, whatever you need). This function will run once after reset.
}
void loop() {
  //Put your main code here. Once the setup-routine has finished this function will keep running in a loop.
}
```

* Open an example sketch, File> Examples > Basics > Blink

```C
//You can write a comment in your code like this
/* or
like 
this 
if you want multiple lines*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); 
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
```
* This program flashes the onbaord LED in 1 second (1000ms) intervals. 
* Notice that LED_BUILTIN, OUTPUT, HIGH, LOW, and the functions digitalWrite(), delay() and pinMode() are all specified in other libraries. 
* Libraries are marked as *.h files, and the Arduino IDE cannot open these. If you are curious download fx. AVRStudio to view them. (AVRStudio is a nice tool for doing more intricate programming of ATmegas by the way.) 
* For example, LED_BUILTIN is defined in pins_arduino.h (located in Program Files (x86)\Arduino\hardware\arduino\avr\variants\standard\pins_arduino.h):
``` C
#define LED_BUILTIN 13
```
Note: Normally you do NOT need to view these files and certainly not change them.

* If you check the [schematic for your board](https://www.arduino.cc/en/uploads/Main/arduino-uno-schematic.pdf) you will find that pin 13 on the board is in fact hooked up to a yellow LED, and also to PB5 on the ATmega. 
* If you keep browsing through the libraries, you will also find that HIGH and OUTPUT are just another way to write 1!
* Therefore the line in the code above could also be replaced by any of the following lines:
```C
pinMode(13,HIGH);
pinMode(PB5,HIGH);
pinMode(LED_BUILTIN,1);
```
* Hit ctrl-r to compile and see if it works!

* Notice the delay function: It basically keeps the processor idling until the specified delay is over. This is not a very efficient use of your processor, and if it gets interrupted by a higher priority interrupt that takes a while to execute it could end up delaying for more or less time. Instead, it would be better to setup your own [interrupt](https://playground.arduino.cc/Code/Interrupts).

* You can also play around with variables. For example, instead of specifying 1000 milliseconds, you could declare a variable:
```C
int i = 1000;
...
delay(i);
```
* If the variable is declared in the very beginning of your code, outside any functions it is called a global variable. Every other function will have access to this one. 
* If a variable is declared within a function, only theat function has access.
* Remember, the ATmega does not have a lot of storage, so it makes sense to make your variables as compact as possible.
```C
unsigned char var = 0; //Takes 1 byte of memory, range [0:255]
char var = 0; //Takes 1 byte, range [-127:127]
int var = 0; //Takes 2 bytes, range [0:2^15]
double var = 0; //Takes 4 bytes, range [0:2^31]
float var = 0; //Takes 4 bytes, and can hold fractions
```

...Add stuff about functions/tabs.


## Tips and tricks

* Many issues can cause the Arduino to reset unexpectedly which will make the robot behavior seem off. This can be things such as a power surge, call to a non-existent interrupt, if the watchdog timer was enabled by mistake, etc. These problems can be hard to see and therefore hard to debug, so it can be a good idea to make it very (visually) clear that your Arduino has reset. An example can be to flash the onboard LED a couple of times. 
