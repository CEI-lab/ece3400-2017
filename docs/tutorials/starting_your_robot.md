2. Create a Start Button Override
If your microphone algorithm doesn’t work during the competition, a “start button” override can be used. A penalty will be assessed if this has to be used (more detailed information to come), but it’s a good alternative compared to having your robot do nothing at all! Note that during the competition, each team’s robot handler will be standing up (not crouched next to the robot), and if the override button needs to be activated because your robot didn’t start at the whistle sound, then you crouch down to activate your robot’s override.


 Write code to recognize intersections, and have your robot respond in some way visually. When your robot turns, make sure that it can keep following the black tape afterwards.


6. Implement a Navigation Algorithm
While you will likely work on this more starting near the end of October, now is a good time to start brainstorming navigation algorithms. A simple naïve implementation is right- and left-hand wall following. In this method, the robot always follows the wall on its right or left, respectively. What kind of maze setups would this robot be able to map completely? What kinds would it fail to map?

For an overview on maze solving algorithms, see this wiki page. Note that since we assume no prior knowledge of the maze layout, only the first four sections are relevant.

When implementing a navigation algorithm, you also must decide on how to map your location. Remember that you are not required to stay on the black tape, but it is suggested that you use the line-following technique for simplicity. Other ways to map location include dead reckoning and using a compass. If you plan on using a mapping method different from line-following, speak to a staff member first.
