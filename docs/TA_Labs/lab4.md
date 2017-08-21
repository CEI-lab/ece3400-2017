# ECE3400 Fall 2017

1.  The TAs should start every lab with a brief introduction to what the students are supposed to do. Make sure everyone knows where the lab-instructions are located. Keep your intros brief so that everyone can get onto their work. 
2.  If the same question appears many times during a session, it is a good idea to ask everyone to pause their work, and discuss the questions with all four teams at the same time. 
3.  Near the end of the lab, when the first teams have started wrapping up, you should again address all the teams, and remind them to write up everything on their webpage, and what is needed to complete the next milestone. 

## Lab 4 TA Reference
### Introduction
This is the final lab, going over radio communication between the robot and the base station. Here are some talking points for the start of the lab, feel free to use as many or few of these as you want.
* **How do radios work?** Go over the basic principles of radio communication. Go over the basic operating principles behind AM or FM radio. Describe what bandwidth and operating frequency and why they are important.
* **Obstacles to radio communication:** Point out where the antenna is on the radios the students will be using. Describe common sources of radio interference and what radio signals can and cannot pass through. Make sure the students understand that metal objects on their robots will absorb or reflect radio waves and could interfere with radio communication.
* **Different methods of updating map information:** Describe different techniques that can be used to send information to the base station in order to update the map. Should the robot send the entire map for every update, or just new information? What data will be stored on the base station and what will be stored on the robot? Keep in mind that the radio offers 2 way communication, so in theory the base station could compute the path finding algorithm and transmit instructions to the robot. Go over the advantages and disadvantages of each approach.
* **General discussion about final competition:** Find how much progress each team has made and how close they are to being prepared for the final competition. Discuss time management techniques as well as the importance of prioritization. Answer questions the students may have about the final competition.

### Team materials
* 2 Nordic nRF24L01+ transceivers
* 3 Arduino Unos (one must be shared with the other sub-team)
* 3 USB A/B cables
* 2 radio breakout boards with headers
* FPGA
* 1 VGA cable
* 1 VGA connector
* 1 VGA switch
* Various resistors (for voltage divider)

### Useful references
[Radio datasheet](images/Radio_Datasheet.pdf) (in images folder)
[8 bit art](https://make8bitart.com/) (useful for prototyping block designs)
[Hex to RGB converter](http://www.rapidtables.com/convert/color/hex-to-rgb.htm)

### Extra help
#### Communication
Agree on a what information will be transmitted over the radio early. The students should make sure that they know what the packet size and format will be as soon as possible. Students should also be aware they have to consider how to deal with dropped packet, as sometimes random interference will cause packets to be dropped.
