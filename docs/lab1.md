# Lab 1: Using the Arduino Uno
## ECE 3400 Fall ’17

### Objective
In this introductory lab, you will learn how to use the various functionalities of the Arduino Uno and the Arduino IDE, as well as the GitHub/Bit Bucket repository system. Your team will brainstorm and construct a simple functional Arduino program using multiple external components and the Arduino Uno. Once you have this basic understanding, you’ll be able to start building your robot!

### Materials
- 1 Arduino Uno
- 1 Continuous rotation servo
- 2 Pushbuttons
- 1 Photoresistor
- Several LEDs (any color except IR)
- 1 Potentiometer
- Several resistors (kΩ range)
- 1 Solderless breadboard

### Pre-lab Assignment
This semester we are allowing each team to choose either GitHub or Bit Bucket as a way of sharing and saving code (Source Control).
By the beginning of your lab session, you should have discussed with your team what tool (GitHub or Bit Bucket) you want to use and have created a GitHub or Bit Bucket account.

GitHub Account: To create a GitHub account go to github.com and request a private account via the educational discount (https://education.github.com/discount_requests/new). There is a document on BlackBoard with more details on GitHub.

Bit Bucket Account: To create a Bit Bucket account go to https://bitbucket.org and click the “get started” button on the upper right-hand corner. Registering with your Cornell (.edu) email address should automatically get you a free academic account.

After creating your account click on the avatar in the upper right hand corner and click on “bitbucket settings” from the drop down list. Then click on “plan details” under “Plans and Billing”. Make sure that the plan level is academic (Regular plan only allows 5 users per private repository). If not click change plan, scroll down to the bottom, click on “apply to have your institution added” and fill in the form.
In addition, you should have reviewed the Arduino Reference (http://arduino.cc/en/Reference/HomePage) page and made yourself familiar with its layout and some basic functions and syntax. Also, read up on how the Parallax Continuous Rotation Servo is used in a circuit:
 http://www.parallax.com/downloads/continuous-rotation-servo-documentation.

### Notebook Documentation
Throughout this lab and ALL labs, remember to have each team member document their steps and experiences in their own lab notebook. Notebooks should contain personal notes, schematics, diagrams, and documentation of results and challenges of this lab. These notebooks will be looked over at the end of your lab session to ensure two things: that you were present in the lab (remember: labs are required), and that you are taking good notes. Keep in mind that you will use your notebooks until the end of the final project. The notebooks will keep track of your progress with the labs and project, how the labs tie into the final project. There is a document on BlackBoard with more details about the Lab Notebook – read it and follow it!

### Procedure
1. **Dismantling a robot from last semester**
Your TAs will assign you a robot from last year to dismantle. All of the major components (servo motors, Arduino boards, FPGA boards, batteries, breadboards, soldered protoboards, etc.) are to be placed in appropriate containers as identified by your TAs. You can save any soldered protoboards to practice soldering (see section 7). Do not keep anything for yourselves/your team.

2. **Communicating between the Uno and IDE**   
Split your team into two groups. Each group will need the materials listed above.  

Use a USB A/B cable to connect the Uno to your lab computer. Open up the Arduino IDE and open the “Blink” example code, or “sketch.” Do this by clicking File  Examples  1.Basics  Blink. The code should pop up in a new window. To program your Arduino, click the checkmark to compile your code and then the right-pointing arrow to upload (program) it. Note: When you click the right arrow, your code will automatically be re-compiled, so clicking the checkmark isn’t strictly necessary. The Uno’s on-board LED should blink on and off every second. If the LED does not blink, check that the UNO is connected to the correct COM port by looking at the Tools  Serial Port list.

Once your Uno is working as it should, take a minute to look over the code and understand what it is doing. Arduino code is similar to C and is relatively easy to understand just by looking at it. One of the first things you’ll notice are two functions – setup and loop. All Arduino sketches (programs) require these two functions or they will not compile. The setup function runs only once at the beginning of the program. The loop function executes after the setup function and runs continuously until the Uno is turned off.

Refer to the Arduino Reference (http://arduino.cc/en/Reference/HomePage) to understand what the other functions in the Blink sketch do. If you have any questions, ask!

3. **Modify the Blink Sketch**
Now that you understand the basics of Arduino code, modify the existing code to work for an external LED (instead of the one on-board that is hard-wired to pin 13). Be sure to connect the LED to a digital pin and remember to always put a resistor in series with the LED. Repeat this for each of the digital pins to make sure that all digital pins work.

4. **The Serial Monitor and the Analog Pins**
The Uno has several analog pins that work as an input only. Because of this, it is not necessary to set up the analog pin to be an input. The potentiometer gives a variable resistance depending on how the knob is turned. Figure 1 shows a pinout diagram for the potentiometer (you can access the datasheet for the potentiometer here: http://www.bourns.com/data/global/pdfs/3306.pdf - it is part number 3306F-103). The Uno pins read voltage, not resistance, so set up a simple voltage-divider circuit using the potentiometer and a resistor. Connect the output of the circuit to the analog pin, and be sure to connect the ends of the circuit to the ground and Vcc pins on the Uno. It is wise to put a ~300 Ω resistor in series with anything you connect to a pin, whether it be an input or an output. This way, if you have set something up incorrectly, it is less likely that you will burn out the pin or any connected components.

![Fig. 1](images/lab1_fig1.png)

Using the Arduino Reference webpage as a guide, think about how to set up your setup and loop functions so that the serial monitor outputs the circuit’s analog value every half-second. When defining the analog pin number, use the code int PINNAME = AX;, where PINNAME is your variable name and X is the analog pin number. You can view the serial monitor by clicking on the magnifying glass in the top right corner of the IDE. Of course, the USB A/B cable must be connected to both the Uno and the computer for the serial monitor to work. Repeat the above with all analog pins to make sure that all analog pins work.

While there are examples in the IDE that have code for the serial monitor and analog pins, please try to figure out how to write the code on your own using just the Arduino Reference page for help. If you get stuck, feel free to collaborate with a neighboring group or ask a TA for assistance.

5. **Analog Output**
While the analog pins only work as an input, it is possible to get an analog output signal. The Uno accomplishes this with a pulse-width modulator (PWM) – it is essentially a very fast square wave with differing on and off times. This square wave is effectually averaged out, creating the effect of an analog or fractional output voltage.

To see how this works, use your existing code for the potentiometer reader to change the brightness of an external LED. Connect an LED to a digital pin (in series with a resistor!) and set it up as an output pin. The digital pin must have PWM capability; this is available for pins with a tilde (~) symbol next to them. Then use the analogWrite function to map the potentiometer value to a brightness value.

6. **Connecting Components**
Now that you know how to manipulate analog and digital values and connect components to pins, design a simple circuit that incorporates LEDs, pushbuttons, resistors, and the photoresistor into one program. If you have trouble deciding on a design, feel free to talk to other teams or a TA.

7. **Parallax Servos**
The wheels for your robot will be Parallax Continuous Rotation Servos. They use the already-provided Servo library to operate. Connect one servo to the Uno by hooking up the white wire to a digital pin (set to output) with PWM capability. Pins with PWM capability are marked with a tilde (~). The red wire goes to the 5V output pin, and the black wire goes to ground. Note: Because servos use a lot of power and can be noisy, you’ll eventually connect the red and black wires to an external power supply consisting of rechargeable 5V battery pack (http://www.monoprice.com/product?c_id=108&cp_id=10831&cs_id=1083110&p_id=13087&seq=1&format=2).

To use the Servo library, insert the line #include <Servo.h> at the top of a new sketch. At the bottom right of the Arduino Reference page, you will see a link for libraries. Follow that link to find documentation on the Servo library.

The servos you have are different than standard servos – most servos can only rotate a certain amount, while the Parallax ones you have rotate continuously as wheels do. Because of this difference, it is important to note that calling the Servo function ServoName.write(X);, where X is an integer from 0 to 180 and ServoName is the servo variable’s name, corresponds to a speed rather than a position. If X is 90, the servo will stop. If it is 0, it will rotate one way at full speed, and if it is 180 it will rotate the other way at full speed. Experiment with values of X until you understand how the servo operates.

8. **Soldering**
A video was presented in class on how to solder electronic components (e.g., https://www.youtube.com/watch?v=IpkkfK937mU), and also desolder (e.g., https://www.youtube.com/watch?v=Fxu1LAoqTRA). Feel free to take some time to practice soldering wires and old electronic components (available in the large bin). It’s a really good idea to practice ahead of time to learn the technique to avoid, for example, damaging your actual components. Obey the following rules:
- Wear goggles when soldering
- Tie your hair if it can get in the way of your work
- Wash your hands after soldering
- Clean the solder iron tip often, and when finished (tin it before storing the iron)
- Turn off the soldering station when you are finished
- Clean your work area!

### Wrap-Up
Keep your Arduino Unos and Parallax servos in the box dedicated for your team. All other components can be placed back into their appropriate bins.
You should have documented this lab in your notebook; your documentation should include personal notes, challenges, successes, and applicable diagrams. In addition, your notebook should contain information on the circuit you designed for section 5 of the Procedure. See the Lab and Notebook Writeup document on BlackBoard for guidelines on how to keep notes in your notebook. Remember to have a TA look over, date and sign your individual notebooks before you leave the lab.

If your team is using GitHub, use the GitHub program on the lab computer to save your code. Otherwise, you can download the SourceTree program from https://www.sourcetreeapp.com.

GitHub and Bit Bucket are tools that allow you to share and save code and other documents. Using one teammate’s personal account, add the code from this lab as a repository and share it with other team members. If you need to access this code at a later time, you can “clone” it back onto the computer. If you need any assistance with using GitHub or Bit Bucket, ask a TA. The lab computers will NOT keep any data locally (i.e., on them). Once you log off, the data eventually will be lost (typically overnight). Save your data on a flash drive or other means before you leave the lab.

### Report
See the Lab and Notebook Write-up document on BlackBoard for guidelines on how to write the report. For this lab, the report should include all of what you did in the lab
