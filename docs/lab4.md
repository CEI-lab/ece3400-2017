# Radio Communication
## ECE 3400 Fall ’17

### Objective
In this lab, you’ll be working on the final major component of your project – radio communication. Using the Nordic nRF24L01+ transceivers and the corresponding Arduino RF24 library, you’ll get the robot and video controller to talk to each other. At the end of this lab, you should ideally be able to send messages from one Arduino to the receiving Arduino (simulating actual maze information) and have the FPGA show it on the monitor.

### Materials
- 2 Nordic nRF24L01+ transceivers
- 2 Arduino Unos
- 2 USB A/B cables
- 2 radio breakout boards

### Pre-lab Assignment
This lab will use the RF24 Arduino library. Before you start the lab, look over the reference page (http://maniacbug.github.io/RF24/classRF24.html) and review the primary public interface methods at the top of the page. Make sure that you understand what they do at a high level.

If you are sending a 2-dimensional (3x3, for example) array of chars, what is the size of the array in bytes? Compare this to the maximum payload size of the radio. How many packets are required to send the 3x3 char array?

Now assume that each element in the array has a maximum value of 3. How many bytes can you compress this array into, now that you know this piece of information? How many packets are now required to send the array?

After completing this exercise, decide with your team what information you want to send (The whole maze? Only information for a newly explored area? An update every 3 seconds?), along with how you want to encode it (chars, ints, packed bytes, etc.).

### Notebook Documentation
Throughout this lab and ALL labs, remember to have each team member document their steps and experiences in their own lab notebook. Notebooks should contain personal notes, schematics, diagrams, and documentation of results and challenges of this lab. These notebooks will be looked over at the end of your lab session to ensure two things: that you were present in the lab (remember: labs are required), and that you are taking good notes. Keep in mind that you will use your notebooks until the end of the final project. The notebooks will keep track of your progress with the labs and project, how the labs tie into the final project. There is a document on Blackboard with more details about that.

### Procedure
1. Soldering the PCB
At the lab bench in front of the room, there should examples of soldered radio breakout boards. As in the picture below on the left, solder a double-row socket header onto the board, and a single-row male header on the other side that will plug straight into the Arduino board. BE SURE NOT TO SOLDER THE PCB UPSIDE-DOWN – confirm this with the TA’s if you are not sure. We do not have enough PCBs to allow for students to make this mistake. Solder a long enough plain wire to the 3.3V hole and be sure to plug this into the 3.3V port on the Arduino. If you doubt how to plug the radio into the double-row socket, make sure the ground pins are all connected together.

![Fig. 1](images/lab4_fig1.png)

![Fig. 2](images/lab4_fig2.png)

2. Getting Started
Download the RF24 Arduino library from https://github.com/maniacbug/RF24. Add it to the Libraries folder in your Arduino directory. Then download the “Getting Started” sketch from Blackboard. Do NOT use the “Getting Started” sketch included in the RF24 library – it is incorrect. Replace the Getting Started code in the RF24 library example folder with the one you downloaded from Blackboard. Change the identifier numbers to the ones assigned to your team using the following formula:

2*(3*D + N) + X,

where D is the day of your lab (0 = Monday day, 1 = Monday night, 2 = Wednesday night, 3 = Friday) and N is your team number. X is 0 for one radio and 1 for the other (you need 2 identifiers, which is why this X is included in the formula).

Example: You are Friday Team 9. And so, D = 3, N = 9, and your identifier numbers are then:

2*(3*3 + 9) + 0/1 = 36 and 37 in decimal = 24 and 25 in hex.

You will put these channel numbers (with leading 0s) in the line of code that says

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

 so that it instead says

const uint64_t pipes[2] = { 0x0000000024LL, 0x0000000025LL };

The LL’s mean “long long,” or a 64-bit number. Leave these in.

Program the sketch onto BOTH of your Arduinos (with the radios plugged in and the appropriate channel assigned), and open up the Serial monitors. Type in “T” and hit enter on ONE of the Arduinos. This will put it in Transmit mode. You should see one Arduino sending a timestamp and the other Arduino receiving it.

Once this is working, do some quick experiments with range and channel number. How far do the radios work at the chosen power level? Do you have any dropped packets? Is there any interference?

Note: If you wish to try different power levels, note that the commented values are INCORRECT. The enum names are “RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, and RF24_PA_MAX.” There is no MED value that the code mentions.

Make sure you understand the Getting Started sketch at a high level; it is suggested that you use this sketch as a building block for your own radio code. If you have any questions, ask a staff member.

3. Sending Maze Information
We will now do two exercises for sending maze information – one where the entire maze is sent and one where only new information is sent.

Sending the Entire Maze

 The most intuitive way of sending an entire maze is with a two-dimensional array. Use this 2D char array as an example:

unsigned char maze[5][5] =
{
3, 3, 3, 3, 3,
3, 1, 1, 1, 3,
3, 2, 0, 1, 2,
3, 1, 3, 1, 3,
3, 0, 3, 1, 0,
};

 Modify the Getting Started sketch to send, receive, and display the array using the Serial Monitor. You can choose to pack the array (since the values only go up to 3) or to send them as chars. Keep in mind that will need to keep track of how many packets you expect to receive, and think of a way to correct behavior if a packet is dropped. For example, if you expect to receive 8 packets but only receive 7, then when the first packet comes of another maze update, you’ll think it’s actually the 8th packet and be one off on your counting after that. The RF24 library has an Auto-ACK feature – look at the details of this and think of how enabling or disabling it would affect how you send and encode packets.

Sending New Information Only

 If you don’t want to send the entire maze, an alternative is only sending new information. Take this code for example:

int x_coord = 3; int y_coord = 2; char data = 2;

 It is up to you, again, whether or not you pack this information. As in the first exercise, modify the Getting Started sketch to send, receive, and display the sent information using the Serial Monitor.

Keep in mind though that even if one method may seem easier to implement, there may be unexpected overhead in other elements of the project. Ask yourself how your choice for this portion of the project affects the robot’s logic as well as the video controller logic. What happens if a packet is dropped? Again, how will the Auto-ACK feature affect this?

4. Implement Your Communication Method
Now that you have worked through some basic examples, implement the method that you will use in the final project. Refer to the Report section to see what you should be documenting as you work. At the end of this lab, you should ideally be able to send messages from one Arduino to the receiving Arduino (simulating actual maze information) and have the FPGA show it on the monitor.

### Wrap-Up
Keep all relevant parts of this lab in the box dedicated for your team. All other components, including USB cables, can be placed back into their appropriate bins.

Before leaving the lab ask one TA to confirm that your box only has 2 Arduinos, 2 Breadboards, and no tools.

You should have documented this lab in your notebook; your documentation should include personal notes, challenges, successes, and applicable diagrams.

Use the GitHub program on the lab computer to save your code. GitHub is a tool that allows you to share and save code and other documents. Using one teammate’s personal account, add the code from this lab as a private repository and share it with other team members. If you need to access this code at a later time, you can “clone” it back onto the computer. If you need any assistance with using GitHub, ask a TA.

### Report
See the Lab and Notebook Write-Up document on Blackboard for guidelines on how to write the report.

While working on the Conclusion, make sure that you have well-commented code. Include pros and cons of the method you chose and argue why it is the best choice for your team. Write about how this method affects the robot’s logic for sending the maze and how you might have to interpret it on the receiving Arduino’s side to send it to the FPGA. This lab links the two physical entities of your project together; make sure you have linked it in a smart, thoughtful, and effective way and talk about that in your report.

If you have started working on putting your robot together, include 2-4 pictures of your robot showing the parts that are put together. This is to corroborate your robot with your Cost Breakdown.

The above information should be placed in the applicable sections of Introduction, Diagrams/Design/Analysis, Experimental Results, and Conclusion that are listed in the Write-Up document.

If you have a lot of code, feel free to put it in an Appendix and refer to sections of it throughout your report where necessary. It would be helpful to have line numbers for easy reference. Make sure your code is well commented and formatted.

Submit your robot’s cost breakdown table as it stands when you submit your Lab 4 report as an Appendix.

If you have any questions on what to write in your report or how to format it, please contact the staff.

The grading of these reports will not be based on the effectiveness of your design but entirely upon your documentation and written understanding of the lab. This will include a TA review of your lab notebook that contains notes, design sketches, and results/challenges.
