# ECE3400 Semester Grades

The final semester grade will depend on multiple factors including lab solutions, how well you do in the final competition, websites, and team work. The details can be found below. Be aware that the standard Cornell rules of [ethical conduct](https://www.dfa.cornell.edu/sites/default/files/policy/vol4_6.pdf) apply, and that you can fail the class if you miss more than 2 mandatory meetings.

A total of 200 points will be given, these correspond to the following grades. Please be aware, that the grading system is new, and that we may end up rescaling the spectrum during the semester.

Score | 200-185 | 184-170 | 169-155 | 154-140 | 139-125 | 124-110 | 109-95 | 94-80 | 79-65 | 64-50 | 49-35 | 34-20 | 19-0
----- | --------|---------|---------|---------|---------|---------|--------|-------|-------|-------|-------|-------|-------
Grade	|    A+   |    A    |    A-   |    B+   |    B    |    B-   |  C+    |   C   |   C-  |  D+   |   D   |  D-   |   F 

The score is calculated like this:

* Each lab counts up to 20 points
* Each milestone counts up to 10 points
* The final competition gives up to 20 points 
* The final robot design gives up to 25 points
* The final webpage gives up to 20 points
* Team work scores give up to 15 points

The following sections describe each scheme in detail.

## Grading of Labs

The labs are scored by the TA's Friday on the week after the labs are done. Up to 15 points are given for good solutions, 5 points for clear and comprehensive documentation.

**Delayed solutions will receive 0 score, without exception.** 

In lab 1, the first 15 points are scored by:

* 2 points: Blinking an internal LED
* 2 points: Blinking an external LED
* 2 points: Reading the value of a potentiometer via the serial port
* 2 points: Map the value of the potentiometer to the LED
* 2 points: Map the value of the potentiometer to the servo
* 2 points: Assemble your robot
* 3 points: Driving your robot autonomously

In lab 2, the first 15 points are scored by:

* 2 points: Correct FFT analysis
* 2 points: Working amplifier circuit
* 3 points: Distinguish a 660Hz tone
* 2 points: Working IR sensor circuit
* 3 points: Distinguish an IR treasure blinking at 300 and 400 Hz
* 3 points: Nicely merged code

In lab 3, the first 15 points are scored by:

* 1 point: Reading external inputs to FPGA
* 1 point: Correctly updating a 4-bit array dependent on the inputs
* 2 points: Drawing one box on the screen
* 4 points: Mapping external inputs to four different outputs on the screen
* 1 point: Connecting the FPGA output to the speaker
* 2 points: Outputting a square wave to the speaker
* 4 points: Outputting a tune of at least three different frequencies to the speaker

In lab 4, the first 15 points are scored by:

* 2 points: Sending information wirelessly between Arduino's
* 2 points: Sending the entire maze wirelessly
* 3 points: Updating the maze array, dependent only on the updated robot information
* 1 point: Displaying a full 4-by-5 grid array on the screen
* 3 points: Communicating maze information from the Arduino to the FPGA
* 2 points: Display the robot location on the screen
* 2 points: Distinguish what sites have been visited and which haven't on the screen

## Grading of Milestones

_Milestone 1 will be graded as follows:_

* 2 points: A robot that successfully follows a line
* 3 points: A robot that successfully traverses a grid in a figure eight
* Up to 5 points will be given for implementation (related to the robustness of the solution and the speed of the robot)

_Milestone 2 will be graded as follows:_

* 2 points (total of 10) per different treasure that can be detected and classified

_Milestone 3 will be graded as follows:_

* 4 points: Simulated maze mapping
* 4 points: Real implementation of the maze mapping
* Up to 2 points for efficiency

_Milestone 4 will be graded as follows:_

* 3 points: System that successfully displays the walls in a maze as the robot finds them
* 3 points: System that successfully displays treasures in a maze as the robot finds them
* 2 points: Robot that successfully signals 'done' on the screen when the maze has been mapped
* 2 points: Robot that successfully plays 'done' on the speaker when the maze has been mapped

## Grading of the Final Competition

The final competition follows a detailed grading scheme that is explained [here](Final_Competition.md)

## Grading of System Design and Documentation

_The TA's will award up to 25 points for good system design._

All members on a team will not necessarily be awarded the same number of points.

To earn these points you can for example implement electronic circuits that improve the accuracy of the maze mapping, efficient search strategies, nice FPGA implementation and a great screen display, or new mechanical components to make the robot faster or easier to maintain. If you have tons of spare time, consider using two cooperative robots to map the maze. The sky's the limit!

_The TA's will also award up to 20 points for good website design and documentation._

This will especially pertain to the work done after the labs towards the milestones and the final system design. Examples of things they will assess include:

* Good introductions and problem motivations
* Clarity and thoroughness of documentation
* Intuitive and nice layouts
*	Use of the right tools for analysis and unit testing
* Presence of schematics when applicable
* Presence of simulation results when applicable
* Presence and evaluation of experimental results
* Use of graphs and tables to display results, as well as proper axis and unit labeling
* Presence of design flaws
* Comparative discussion of simulation and experimental results
* Presence of conclusions
* Presence of suggestions for future work/improvements
* You can also gain extra points by making good general tutorials for students in future semesters to use. These tutorials may for instance include ways to implement PID control, in-depth tutorials on ATmega timers, new ways to make 3D parts, etc. 

## Grading of Team Work 

15 points will be given through self-assessment within the team.

Three times over the semester we will practice giving and receiving constructive criticism. The point is not to complain, but to make sure everyone contributes their best towards the final project. Each student will be asked to distribute 100 points between their team members dependent on their contribution to the team work. The accumulated points will be normalized to the group size and scaled to between 0 and 10 points towards the final grade.

Each team will meet with the professor and discuss the reasoning for their point distribution. Remember that many qualities can be considered a valuable contribution to a team: technical strength, dedication/persistence, optimism, creativity, leadership and maintaining a perspective, role of initiation, and detail oriented thinking.




