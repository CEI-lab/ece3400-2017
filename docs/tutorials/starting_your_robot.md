# Starting on Your Robot
## ECE 3400 Fall ’17

### Objective
This handout is meant to accompany Lab 3 and can be referred to for the rest of the semester. While a part of your team works on the VGA code and Arduino/FPGA interface, the rest of your team can focus on getting the basics done for your robot’s operation. This may include calibrating the wheels, starting on line following, or incorporating basic sensors. Note that starting near the end of October, there will be 3 technical deliverables (similar to lab reports) that will serve the purpose of reaching milestones towards building your fully functioning robot.

When in doubt, ask! Don’t assume anything…

### Materials
Materials vary.

### Pre-lab Assignment
There is no pre-lab assignment for this accompanying handout; Lab 3’s pre-lab assignment is listed on the regular Lab 3 handout. Don’t forget the Pre-Lab meeting (see corresponding handout)!

### Notebook Documentation
Throughout this lab, remember to have each team member document their steps and experiences in their lab notebook. Notebooks should contain personal notes, schematics, diagrams, and documentation of results and challenges of this lab.

### Choosing Components
Your team has a budget of $100 to use for your robot. Your team will keep a running tally of the cost breakdown. The cost breakdown is as follows:
- Line (grayscale) sensors: $3
- IR sensors: $7
- Parallax servos (not continuous rotation): $15
- Basic components (resistors, capacitors, LEDs, etc.): $0
- 3D printed, laser cutting: $0
- Custom orders: We can buy parts for you, but the cost of the parts plus shipping goes towards your $100 total available budget.
- If you spend your own money to purchase/add components, you will need to provide the receipt to the staff, and the cost will go towards the total available budget. Shipping charges will also count towards your total $100 budget.
- Used/salvaged parts can be used: you will clear those with the staff and the parts’ list price will be used to count towards the total available budget. Shipping charges will also count towards your total $100 budget.

If there are other sensors or components you’d like to use, speak to the staff as early as you can. If your team really wants to use ultrasonic sensors, you can, but be warned that it will be tricky to use them appropriately in a maze environment. The staff will assign a cost to the component and order it, if approved. It may take up to two weeks to get your parts in.

### Suggested Tasks
Again, note that starting near the end of October, there will be 3 technical deliverables (similar to lab reports) that will serve the purpose of reaching milestones towards building your fully functioning robot.

1. Begin to Assemble the Robot

2. Create a Start Button Override
If your microphone algorithm doesn’t work during the competition, a “start button” override can be used. A penalty will be assessed if this has to be used (more detailed information to come), but it’s a good alternative compared to having your robot do nothing at all! Note that during the competition, each team’s robot handler will be standing up (not crouched next to the robot), and if the override button needs to be activated because your robot didn’t start at the whistle sound, then you crouch down to activate your robot’s override.

3. Operating the Wheels
In Lab 1, you learned how to use the Parallax Continuous Rotation Servos. Attach the wheels to two of these servos and write basic code for going forward, backward, and turning 90 degrees. When you start to integrate line-following, you might edit this code so the wheel speeds change in order to stay on the black tape.

4. Integrate Line Following
Use the grayscale line sensors to integrate line following into your robot. You will need to discover what values correspond to staying on the line versus veering off of it. With that knowledge, decide how you will relate those values to setting wheel speeds.

 Write code to recognize intersections, and have your robot respond in some way visually. When your robot turns, make sure that it can keep following the black tape afterwards.

 For line following, we recommend that you use PID control. The wiki page provides a good overview if you are not familiar with the concept, particularly the second and third sections: Control loop basics and PID controller theory.

 PID will be discussed in class.

 For example code, read through this Polulu library reference for line following. We will not be using the same line sensors, so the library won’t be installed/used directly. However, reading through the example will give you an idea of how PID control can be used for line following, particularly the command reference for readLine() and the bottom section on PID control.

5. Sense walls
Use the IR distance sensors to sense walls near the robot. Use the IR sensor’s datasheet to map values to actual distances, and then break those distances down into blocks. Do you need to know that a wall is 6 inches away, or that it is simply one block ahead? Think about this and make a design choice.

6. Implement a Navigation Algorithm
While you will likely work on this more starting near the end of October, now is a good time to start brainstorming navigation algorithms. A simple naïve implementation is right- and left-hand wall following. In this method, the robot always follows the wall on its right or left, respectively. What kind of maze setups would this robot be able to map completely? What kinds would it fail to map?

For an overview on maze solving algorithms, see this wiki page. Note that since we assume no prior knowledge of the maze layout, only the first four sections are relevant.

When implementing a navigation algorithm, you also must decide on how to map your location. Remember that you are not required to stay on the black tape, but it is suggested that you use the line-following technique for simplicity. Other ways to map location include dead reckoning and using a compass. If you plan on using a mapping method different from line-following, speak to a staff member first.

### Wrap-Up
Keep your assembled robots and any relevant parts in the box dedicated for your team. All other components can be placed back into their appropriate bins.

You should have documented this lab in your notebook; your documentation should include personal notes, challenges, successes, and applicable diagrams.

### Report
Refer to the Lab 3 Handout for information on writing the report. There should be a section in your report dedicated to outlining your work relevant to this accompanying handout.
