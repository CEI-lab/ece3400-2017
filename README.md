# ECE 3400 Intelligent Physical Systems 

**Cornell, Fall 2017, room: PH 414**

**Instructor:** Kirstin Petersen (khp37)

**TA's:** Ryan O'Hern (rmo26), Claire Chen (clc288), Christopher Fedors (cjf83), Daniel Kim (dsk252), Vaidehi Garg (vg254), Vidya Ramesh (vr236)

**Piazza page:** ADD LINK!

## Course Description

Students will engage in a holistic design approach to Intelligent Physical Systems which can perceive, reason about, and act upon their environment. This course will expand on the ECE 2000-level courses, and include topics on algorithms, field programmable gate arrays, wireless communication, sensors, actuators, power, and mechanics. Students will learn the value and trade-offs between theory, simulation, and physical implementations, and gain familiarity with rapid prototyping techniques, system debugging, team work, leadership skills, time management, and how to disseminate work to a broader audience through webpages.

_Specific outcomes include:_

 - The ability to apply specific design methodologies to the course project
 - The ability to evaluate what problems are best solved in software, electronics, or mechanics; as well as the trade-offs between theory, simulation, and practical implementations.
 - Efficient team work, as a member and as a leader.
 - Effectively communication skills through online media.
 - Awareness of professional and ethical responsibilities in the context of Intelligent Physical Systems.

Prerequisites include ECE 2100  ECE 2200 and ECE 2300.  Recommended prerequisite: ECE 2400 (or equivalent).
All information is gathered on this page; no additional textbooks are required.

## Semester Project

In teams of 6-8 people, you will design, fabricate, and program a robot to explore a maze. The robot microcontroller will be based on an Arduino Uno; the default propulsion method will be differential drive with continuous rotation servos. The robot will traverse the maze by following black lines on a white floor; it must also be able to detect walls, an audible start signal, and treasures emitting infrared light at different frequencies. The robot must continuously transmit its progress wirelessly to a base station (also based on Arduino Uno). This base station will communicate with an FPGA that in turn must drive a screen through a VGA interface. Points will be awarded for speed, accuracy, and innovative design methods. The entire robot can cost no more than $100; this chart shows how the price is calculated.

All designs must be documented throughout the semester on a group website. The goal is for these websites to be used as a source of reference for future classes. Accordingly, they will be graded with respect to thoroughness and clarity. To give teams a competitive advantage, we ask everyone to keep explicit code and circuit designs private until the end of the semester, however. 

[Rules and final scoring chart](docs/Grading/)

## Team Composition

The teams will be composed by the TA's and lecturer without exception. 

Teams will be dependent on lab-time sign-up, student skillsets, and personalities. Before midnight August 28th please fill out these Google forms such that the teams can be formed immediately. 

All labs are divided into two sub-labs. To ensure a good mix, it is required that you keep switching partners for the different labs. For example, if student A-F is a team; lab 1 should be solved by A-B-C and D-E-F; lab 2 by A-C-D and B-E-F; lab 3 by A-D-E and B-C-F; and lab 4 by A-E-F and B-C-D.  

We will host internal team evaluations and practice constructive critiscism. Receiving and giving profesional feedback may be uncomfortable at first, but it is a skill that will help you in any future career.

This [folder](docs/Grading/) includes documents detailing how students will be graded. Be aware that a lot of changes has been made for Fall 2017 and that the score-chart may be changed throughout the semester.  

## Schedule and Hand-Outs

We will cover several topics this semester, roughly the order/timing will be:

          week1         |               week2                         |      week3             |         week4                   
------------------------|---------------------------------------------|------------------------|--------------------------------
Intro, IPS fundamentals | Embedded Control, team work/time management | Sensors and filters    | Actuators and control 


          week5         |               week6                         |      week7             |         week8                   
------------------------|---------------------------------------------|------------------------|--------------------------------
           FPGA         |           FPGA, VGA                         | Wireless Communication |  Prototyping


          week9         |               week10                        |      week11            |         week12                   
------------------------|---------------------------------------------|------------------------|--------------------------------
      Algorithms        |           Algorithms                        | Prototyping            | Power, and public communication


          week13        |               week14                        |      week15            |         week16                   
------------------------|---------------------------------------------|------------------------|--------------------------------
      Debugging IPS     |            IPS Ethics                       | IPS characterization   |      Competition                     


- XXX Deadline: Fill in Google Forms
- XXX Deadline: The websites will be graded for contents on lab 1
- XXX Deadline: The websites will be graded for contents on lab 2
- XXX Deadline: The websites will be graded for contents on lab 3
- XXX Deadline: The websites will be graded for contents on lab 4
- XXX Deadline: The websites will be graded for contents on Milestone 1
- XXX Deadline: The websites will be graded for contents on Milestone 2
- XXX Deadline: The websites will be graded for contents on Milestone 3
- XXX Deadline: The websites will be graded for contents on Milestone 4

- [Lab 1 Microcontrollers](docs/lab1.md)
- [Lab 2 Signal Processing](docs/lab2.md)
- [Lab 3 Digital Logic](docs/lab3.md)
- [Lab 4 Wireless Communication](docs/lab4.md)
- Milestone 1 Recognize Start-Signal
- Milestone 2 Move on the Grid
- Milestone 3 Display Updates on the Screen
- Milestone 4 Navigate the Maze
- Competition

Here is the full link to the topics we are expected to cover in class. Please be aware that this is a tentative schedule that will change throughout the semester. [ADD]

# Tutorials and Helpful links

We have and will continue to upload helpful tutorials and links on this webpage. We would love for you to contribute, please contact the TA's to do this!

**Related to GitHub**

- [Ryan, add links!]
- [Markdown cheat sheet](https://guides.github.com/pdfs/markdown-cheatsheet-online.pdf)

**Team Alpha Repository**

This is the repository for the team of TA's that solved all the labs during the Summer of 2017. Please use this website for support and inspiration; no credits will be given for close copies of these solutions. Also, the TA's were under strict timelines - hopefully you will upload more comprehensive and better websites over the course of the semester.

**Related to Control**

- [Arduino Uno online references and tutorials](https://www.arduino.cc/en/Reference/HomePage)
- [PID control]
- [Helpful FPGA-related Links and Tips](docs/FPGA_resources.md)

**Related to fabrication:**

For the first time ever, we have a Skunkworks available to the class. This is located in PH427. Please be aware that you will only have access to this lab after you have taken a safety training, and in the presence of a TA. 

- A zip file "ECE3400_Fall 2017_SolidWorks.zip", with all the mechanical parts drawn in SolidWorks can be found [here](docs/)
- [Tutorials on Solid Works]
- [Tutorials on Autocad]
- [How to use the XYYZ 3D printer]
- [How to use the Epilog laser cutter]
- [Tutorials on Eagle]
- [How to etch your own PCB]
- [How to solder components and wires]
- [Wiring a robot]
- [What goes on inside a servo?]



**Related to debugging**

- [How to build your own oscilloscope with an Arduino]
- [Simple Matlab program to read in data from the serial port]
- [Simple Matlab program to simulate maze search]
- [This folder](docs/simulation/) has software in Java, Processing, Matlab, and C++ for simulating robot search




