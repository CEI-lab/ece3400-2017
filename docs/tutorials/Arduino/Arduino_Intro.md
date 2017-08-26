# ECE3400 Fall 2017
## Introduction to Arduinos

*By Kirstin Petersen, Aug 25th 2017.*

This tutorial gives a very brief introduction to Arduino Unos. (Basically everything we went over in Lecture 2, but more legible).

### Arduino IDE

Arduino IDE is one of the most popular popular tool for programming Arduino boards. IDE stands for Integrated Development Environment. The interface is meant to enable people with very little experience to program exciting robots/devices. This also means that it integrates a large number of libraries automatically to make sure everything works. 

* Open Arduino IDE
* Make sure that the IDE knows the correct board you are working with (> Tools > Board > Arduino/Genuino Uno)
* It will automatically open the last sketch you had opened, or if this is your first time it will open a blank sketch that looks like this:

```C
void setup() {
  //Put your setup code here; this function will run once after reset. 
  //(initialize input/output pins, analog pins, ADC, timers, whatever you need). 
}
void loop() {
  //Put your main code here. Once the setup-routine has finished this function will keep running in a loop.
}
```

### Libraries

* Open an example sketch, File> Examples > Basics > Blink

```C
//You can write a comment in your code like this
/* or like this if
you want to encase multiple lines*/

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
* This program flashes the onboard LED in 1 second (1000ms) intervals. 

* Notice that LED_BUILTIN, OUTPUT, HIGH, LOW, and the functions digitalWrite(), delay(), and pinMode() are all specified in other libraries. Normally to include a new library you add "#include <library_name>" in the beginning of your file. But since these are all standard the compiler automatically looks for them. 
* Libraries are saved as .h files, and the Arduino IDE cannot open these. If you are curious, download fx. AVRStudio to view them. (AVRStudio is a nice tool for doing more intricate programming of ATmegas by the way.) 
* For example, LED_BUILTIN is defined in pins_arduino.h (located in Program Files (x86)\Arduino\hardware\arduino\avr\variants\standard\pins_arduino.h):
``` C
#define LED_BUILTIN 13
```
Note: Normally you do NOT need to view these files and certainly not change them.

* If you check the [schematic for your board](https://www.arduino.cc/en/uploads/Main/arduino-uno-schematic.pdf) you will find that pin 13 on the board is in fact hooked up to a yellow LED, and also to PB5 on the ATmega. 
* If you keep browsing through the libraries, you will also find that HIGH and OUTPUT are just another way to write a logic 1!
* Therefore the line in the code above could also be replaced by any of the following lines:
```C
pinMode(13,HIGH);
pinMode(PB5,HIGH);
pinMode(LED_BUILTIN,1);
```
* Hit ctrl-r to compile ("verify") and see if it works!

### Delay-function
* Notice the delay function: It basically keeps the processor idling until the specified delay is over. This is not a very efficient use of your processor, and if it gets interrupted by a higher priority interrupt that takes a while to execute it could end up delaying for more or less time. Instead, it would be better to setup your own [interrupt](https://playground.arduino.cc/Code/Interrupts).

### Variables
* You can also play around with variables. For example, instead of specifying 1000 milliseconds, you could declare a variable:
```C
int i = 1000;
...
delay(i);
```

* If the variable is declared in the very beginning of your code, outside any functions it is called a global variable. Every other function will have access to and can change this one. 
* If a variable is declared within a function it is called a local variable, and only that function has access/can change it.
* Remember, the ATmega does not have a lot of storage, so it makes sense to make your variables as compact as possible.
```C
unsigned char var = 0; //Takes 1 byte of memory, range [0:255]
char var = 0; //Takes 1 byte, range [-127:127]
unsigned int var = 0; //Takes 2 bytes, range [0:2^16]
int var = 0; //Takes 2 bytes, range [0:2^15]
double var = 0; //Takes 4 bytes, range [0:2^31]
float var = 0; //Takes 4 bytes, and can hold fractions
```

### Functions
* During the course of this project your code will get very long, and it will be easier for you if you split up your code into separate functions. For example, the blinky-code above could also be written as:
```C
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {
  blink_LEDS();
}

void blink_LEDS(void) {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
```
* The 'voids' note that the function takes no parameters and returns none. 
* We could also change the function to take an input, e.g.:
```C
void loop() {
  blink_LEDS(4); //Blink LEDs four times
  while(1); //This is always true, therefore after blinking the LED the processor will idle forever
}

void blink_LEDS(char repeats) {
  for(char i=0; i<= repeats; i++) 
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
  } //For every time this for-loop runs, i is incremented by one - it finishes when i is greater than repeats
}
```
* We can also change the function to return a variable
```C
void loop() {
  while(!blink_LEDS(4)); //Call blink LEDs until the function returns true (done)
  while(1); 
}

bool blink_LEDS(char repeats) {
  for(char i=0; i<= repeats; i++) 
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
  } //This for-loop finished when i is greater than repeats
  return 1;
}
```
* Of course this is a stupid example, because blink_LEDS() can't fail to execute, but you get the drift!

* If your main file gets too cluttered, you can also move the function into a separate tab. Make sure your main file is saved first (saving it will automatically create a folder with the same name as the file). Then, in the upper right corner of the IDE, click the downward facing arrow and make a new tab. Or press ctrl+shift+n. It will ask you for the name of the new tab and then create an .ino file in your folder with the same name. Any functions you move over into the new tab can be called directly from your main routine.

## Tips and tricks

* Many issues can cause the Arduino to reset unexpectedly which will make the robot behavior seem off. This can be things such as a power surge, call to a non-existent interrupt, if the watchdog timer was enabled by mistake, etc. These problems can be hard to see and therefore hard to debug, so it can be a good idea to make it very (visually) clear that your Arduino has reset. An example can be to flash the onboard LED a couple of times. 

* The compiler isn't perfect. Here are some standard issues you'll run into during the class: 1) It doesn't automatically save your code when you compile. 2) It doesn't detect issues such as saving too big a number in a variable. 

* Happy coding! You'll go through many functions in Lab 1, you can also try out stuff at home by following [these instructions](https://www.arduino.cc/en/Tutorial/BuiltInExamples)
