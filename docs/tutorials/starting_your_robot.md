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
