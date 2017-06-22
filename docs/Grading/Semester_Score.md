# ECE3400 Semester Grades

The final semester grade will depend on multiple factors including lab solutions, how well you do in the final competition, websites, and team work. The details can be found below.

A total of 200 points will be given, these correspond to the following grades. Please be aware, that the grading system is new, and that we may end up rescaling the spectrum during the semester.

Score | 200-185 | 185-171 | 170-155 | 154-140 | 139-125 | 124-110 | 109-95 | 94-80 | 79-65 | 64-50 | 49-35 | 34-20 | 19-0
----- | --------|---------|---------|---------|---------|---------|--------|-------|-------|-------|-------|-------|-------
Grade	|    A+   |    A    |    A-   |    B+   |    B    |    B-   |  C+    |   C   |   C-  |  D+   |   D   |  D-   |   F 

The score is calculated like this:

* Each lab counts up to 20 points
* Each milestone counts up to 10 points
* The final competition gives up to 20 points 
* The final robot design gives up to 25 points
* The final webpage gives up to 20 points
* Team work scores give up to 15 points

The following sections describe each point in detail.

## Lab grading rubrics

The labs are scored by the TA's Friday on the week after you completed the lab. Delayed solutions will receive 0 score, without exception. Up to 15 points are given for good solutions, 5 points for clear and comprehensive documentation.

In lab 1, the first 15 points are scored by:

* 2 points: Blinking an internal LED
* 2 points: Blinking an external LED
* 2 points: Reading the value of a potentiometer via the serial port
* 2 points: Map the value of the potentiometer to the LED
* 2 points: Map the value of the potentiometer to the servo
* 2 points: Assemble your robot
* 3 points: Driving your robot autonomously

In lab 2, the first 15 points are scored by:

* 2 points: For correct FFT analysis
* 2 points: For good amplifier circuit
* 3 points: To distinguish a 660Hz tone
* 2 points: For a good IR sensor circuit
* 3 points: To distinguish an IR treasure blinking at 300 and 400 Hz
* 3 points: For merging your code nicely

In lab 3, the first 15 points are scored by:

* 1 point for reading external inputs to FPGA
* 1 point for correctly updating a 4-bit array dependent on the inputs
* 2 points for drawing one box on the screen
* 4 points for mapping external inputs to four different outputs on the screen
* 1 point for outputting a signal from the FPGA to the speaker
* 2 points for outputting a square wave to the speaker
* 4 points for outputting a tune of at least three different frequencies to the speaker

In lab 4, the first 15 points are scored by:

* 2 points for sending information wirelessly between Arduino's
* 2 points for sending the entire maze wirelessly
* 3 points for updating the maze array, dependent only on the updated robot information
* 1 point for displaying a full 4-by-5 grid array on the screen
* 3 points for communicating maze information from the Arduino to the FPGA
* 2 points to display the robot location on the screen
* 2 points to differentiate what sites have been visited and which haven't on the screen

Milestone 1 will be graded as follows:

* 2 points will be given for a robot that successfully follows a line
* 3 points will be given for a robot that successfully traverses a grid in a figure eight
* Up to 5 points will be given for implementation (related to the robustness of the solution and the speed of the robot)

Milestone 2 will be graded as follows:

* 2 points (total of 10) per different treasure that can be detected and classified

Milestone 3 will be graded as follows:

* 4 points for simulated robot maps an entire maze
* 4 points for a real implementation of the maze mapping
* 2 points for efficiency

_Milestone 4 will be graded as follows:_

* Up to 3 points for a robot that successfully displays the walls in a maze
* Up to 3 points for a robot that successfully displays treasures in a maze
* Up to 4 points for a robot that successfully signals 'done' (on screen and speaker)

_The final competition follows a detailed grading scheme that is explained in ""_

_The TA's will award up to 25 points for good system design._ 

All members on a team will not necessarily be awarded the same number of points: 

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
* Presence of future work suggestions
* You can also gain extra points by making good general tutorials for students in future semesters to use. These tutorials may for instance include ways to implement PID control, in-depth tutorials on ATmega timers, new ways to make 3D parts, etc. 

_10 points will be given _

