# ECE3400 Fall 2017
## Lab 2: Analog Circuitry and FFTs

### Objective
In this lab, you will add sensors to your robot, and make analog circuits and a digital filter to interface with the Arduino. One is a microphone circuit that will detect a 660Hz whistle blow signifying the beginning of your maze mapping. The other will capture inputs from an IR sensor to detect and distinguish treasures. 

### Pre-lab Assignment
Before you start your lab, you should have looked over the Open Music Labs Arduino FFT library documentation. If you are unfamiliar with Fourier Transforms and Fast Fourier Transforms (FFTs), be sure to check out online resources or textbooks to review the concepts. Your website will be expected to have a sufficient explanation of the basic FFT algorithm.

Look over the Open Music Labs Arduino FFT library example sketches. You’ll see that they use the internal microcontroller’s Analog-Digital Converter (ADC) as fast as it can convert. Look this up online and see how fast it goes, and then compare that to the Arduino’s analogRead function. Is it necessary to use the ADC directly, or is analogRead fast enough? This will depend on your application (reading 660Hz sine wave, or ~10kHz treasure). What might be some concerns of using either method? What’s the normal range of a human voice? Are the harmonics of human speech an issue? What is the frequency of the flourescent lights in the room? Can they interfere with your IR sensor?

For testing in the lab, it’s a good idea to install an App on your phone that will generate the 660 Hz tone. There are many free Apps for this like Tone Generator for example.

It would be wise to design some simple analog amplifying and filtering circuits so you can add them as necessary once you’re in lab checking out the amplitude of your analog signals. What are some good cutoff frequencies to use in your design? How big of a gain and DC offset is appropriate? (Remember that the Arduino inputs must be between 0 and 5V.)

### Documentation
Throughout this lab and ALL labs, remember to document your progress on your website. Add anything that you think might be useful to the next person doing the lab. This may include helpful notes, code, schematics, diagrams, photos, videos, and documentation of results and challenges of this lab. You will be graded on the thoroughness and readability of these websites. 

Be sure to note on the website what work is carried out by whom. And remember that, if at all possible, you are expected to form different sub teams in every lab.

### Procedure

Split into two teams. 

The acoustic team will need the following materials:
- Arduino Uno
- Electret microphone
- 1 µF capacitor
- 300 Ω resistors
- ~3 kΩ resistor
- Various other components, as needed

The optical team will need the following materials:
- Arduino Uno
- IR receiver
- 300 Ω resistors
- Various other components, as needed

*Unit tests are highly suggested. Test the output of the sensor directly with the scope; check your analog amplifier with a voltage supply; check analog/digital filters with a signal generator; then combine all the pieces and check again.*

#### Download the Open Music Labs FFT library

* Open Music Labs’ FFT page, scroll down and download the newer FFT library folder. Extract this, and then go to My Documents > Arduino > Libraries and put the FFT library folder inside of it. If you have the Arduino IDE open, close it and then restart the program (not the computer) so that it can update accordingly.

* Use the example sketch to start coding. On the FFT webpage, you will find some good, solid documentation on how to use the library. You should have reviewed this before the lab. In addition, the library you just installed has an example sketch that reads in values from Analog Pin 0 and outputs the frequency bin magnitudes via the serial monitor. Check this code out, and consider using it as a base for your microphone circuit code. You should have thought about possible modifications to this code from when you did the prelab. Remember that your goal is to be able to match a signal to its frequency. For the competition, a sine wave at 660 Hz will be emitted from a set of speakers to signal the start of the race.

To program your Arduino, click the checkmark to compile your code and then the right-pointing arrow to upload (program) it. Note: When you click the right arrow, your code will automatically be re-compiled, so clicking the checkmark isn’t strictly necessary. If it doesn’t work, check that it is connected to the correct COM port by looking at the Tools  Serial Port list.

Refer to the Arduino Reference (http://arduino.cc/en/Reference/HomePage) for helpful functions and syntax as needed.

3. **Assemble your microphone circuit**
The basic circuit for your electret microphone is as follows:

![Fig. 1](images/lab2_fig1.png)
Image from Wikipedia

It is suggested that you use a 1 µF capacitor and a ~3 kΩ resistor. You only need these components if you are not adding amplifiers and filters yet – otherwise, just plug one end of the microphone to ground and the other straight into your analog circuitry. It is up to your team to determine if and what kinds of amplifiers and/or filters will be necessary to register the whistle blow. If you decide to add filters and/or amplifiers, feel free to reference textbooks and the Web. Just be sure that you can fully describe and explain your circuitry choices and how they work when you write your lab report (as well as cite your sources).

The Arduino’s analogRead function can only measure signals from 0 to 5 volts, so make sure that your circuit’s output is between these ranges (hint: you might want to create a DC offset).
It is wise to put a ~300 Ω resistor in series with anything you connect to a pin, whether it is an input or an output. This way, if you have set something up incorrectly, it is less likely that you will burn out the pin or any connected components.

4. **Finish coding and debugging your microphone circuit**
You will likely find that plugging in your circuit and running your code will not produce expected results. Remember when you debug that the oscilloscope on your lab bench is an invaluable tool both for your physical circuitry and for your Arduino. The waveform generator will also be an asset in debugging your code.

Also MATLAB, which is installed on the lab computers, is another invaluable tool for debugging. You can use MATLAB to import values from a serial port and plot a graph of your signal. Use the myserialport = serial(comport, ‘BaudRate’, budrateneeded) to initialize a serial port. Set the comport parameter to the port that your Arduino is connected to (under Tools>ports in the Adriano program) and the budrateneeded parameter to 9600. Use the fopen(myserialport) to open the serial port. Read from the port using fscanf(myserialport,’%i’) and plot the value read. Close the port using fclose(myserialport) after you’re done reading.

As always, feel free to talk to other groups or a TA if you need assistance.
Remember to do adequate error-checking so that your robot responds reliably to the whistle blow. Otherwise, your performance will be penalized and you will get a late start on mapping the maze.

5. **Assemble and code your additional circuit**
Before you start creating your secondary circuit, make sure that a TA has checked off on it first. This design and implementation is largely up to you, so make sure you have a solid game plan before you come into the lab.
One example for your additional circuit is a thresholded grayscale sensor. Using a white LED, a photoresistor, and Schmitt Trigger, you can design a circuit that outputs a “1” when it is on top of the black tape and a “0” when it is not (or vice versa). Doing this is helpful because packaged grayscale sensors have an analog output, which you don’t have that many pins for. Freeing up an analog pin for another sensor could be helpful when you are designing your robot.

There are countless circuits you could invent that would aid in your design. Remember that your circuit does not need to be complex – only useful.

### Wrap-Up
Keep your circuits and Arduino Unos in the box dedicated for your team. Any other unused components can be placed back into their appropriate bins.

You should have documented this lab in your notebook; your documentation should include personal notes, brainstorms and ideas for your code, challenges, successes, and applicable diagrams. In addition, your notebook should contain information on the circuits you designed for sections 3 and 5 of the Procedure.

Use the GitHub/SourceTree program on the lab computer to save your code. Using one teammate’s personal account, add the code from this lab as a private repository and share it with other team members. If you need to access this code at a later time, you can “clone” it back onto the computer. If you need any assistance with using GitHub/Bitbucket, refer to the tutorial on Blackboard or ask a TA.

### Report
See the Lab and Notebook Write-up document on BlackBoard for guidelines on how to write the report.

The report for this lab should not be longer than four pages. It should include three sections:

1. One to two pages with an introduction, statement of the purpose of the lab, and an overview of your circuit designs.

2. Two to three pages (OK if it's more) with diagrams and documentation of your designed circuits and programs, along with a description of the methods used (including FFT). This means that you need to explain clearly why you use the FFT, how you do it (explain the filtering, how you implement the filtering, how the filters work with schematics), and how your circuits work (calculations, simulations, measurements, etc.). Everything needs to be explained.

3. One page for any issues encountered, results, a short explanation on how the lab fits with the final project, and any suggested improvements for the lab.

4. In addition to submitting a hard copy of your report in lab, upload an electronic version of your report (with all clearly commented code) to Blackboard.

The grading of these reports will not be based on the effectiveness of your design but entirely upon your documentation and written understanding of the lab. This will include a TA review of your lab notebook that contains notes, design sketches, and results/challenges.
