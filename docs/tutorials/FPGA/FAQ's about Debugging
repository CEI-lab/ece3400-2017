# FAQ's about debugging 

* Strange bugs such as not being able to blink the LED’s on the FPGA board, not being able to compile a project, not being able to run a sample code that you’ve download from the website and know that it works.
  Try the following fixes:
  *	Restart the computer
  *	If you are using your own laptop, maybe there is a problem with how you installed the Quartus drivers- so switch to a lab computer.
  *	If the sample code is not displaying to the screen- check that the VGA cords are all connected in the correct configuration. Sometimes cords are unplugged when people are moving monitors around. 
  *	Check the pinout! This is maybe one of the most common issues- the DAC is connected incorrectly. Make sure you are using the correct side of the GPIOs (GPIO_1 or GPIO_0) and that you are counting the GPIO’s by their GPIO1_## not by the physical pin number from counting. 
  *	Empty the documents/downloads folder and redownload the project file- there have been problems where file naming has been an issue. If you’re using one of the lab computers sometimes files have been downloaded by other groups and have the same name, which seems to make Quartus confused. 
  
* Timing issues when updating the screen (cycles through pixels), screen displaying blocks with fuzzy edges, only displaying half of the screen. 
  * Make sure you have a common ground- this is the most ‘common’ issue! If you are sending/receiving from your Arduino- make sure that the Arduino GND and FPGA GND are connected!
* Problems writing/reading Pin 0/1 on Arduino. 
  * Pin 0 and Pin 1 are RX and TX pins- writing and reading to these pins will not work if the Arduino code has Serial.begin.
* If there is a small thin line of pixels in the wrong color/where it shouldn't be.
  * Check inequality signs- one of them should be >= or <=, can't just have < and > for boundaries. 
