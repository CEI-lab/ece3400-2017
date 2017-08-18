# ECE3400 Fall 2017
## Lab 4 TA Reference
### Introduction
This is the final lab, going over radio communication between the robot and the base station. Here are some talking points for the start of the lab, feel free to use as many or little of these talking points as you want.
* **How do radios work?** Go over the basic principles of radio communication. Go over the basic operating principles behind AM or FM radio. Describe what bandwidth and operating frequency and why they are important.
* **Obstacles to radio communication:** Point out where the antenna is on the radios the students will be using. Describe common sources of radio interference and what radio signals can and cannot pass through. Make sure the students understand that metal objects on their robots will absorb or reflect radio waves and could interfere with radio communication.
* **Different methods of updating map information:** Describe different techniques that can be used to send information to the base station in order to update the map. Should the robot send the entire map for every update, or just new information? What data will be stored on the base station and what will be stored on the robot? Keep in mind that the radio offers 2 way communication, so in theory the base station could compute the path finding algorithm and transmitt instructions to the robot. Go over the advantages and disadvantages of each approach.
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
[Radio datasheet](images/Radio_Datasheet.pdf)
