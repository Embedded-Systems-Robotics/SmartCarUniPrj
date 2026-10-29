# SmartCarUniPrj

This project was made by:
- Lawrence Abou Karroum (Personal Webiste: https://lawrence-abou-karroum.web.app/, linkedin: )
- Ahmad Mansour (linkedin: )
- Majd Nasrallah (linkedin: )
- Ziad hamede (linkedin: )
It was the final project in the Embedded Systems Lab course at the Univeristy of Balamand, and the goal was to achieve three modes in the project of which they were successfully made and tested. (the mode will be mentioned later on below)

--
In this repository three section:
    - Controller: this is the controller of the car, it is used to control the car manually, and switching between modes (mentioned below)
    see the following image:
    Controller_Board.png
    - RobotCar: this folder include the code of the car, it allows it to navigate autonomously and has a line following code
    see the image:
    Robot.png

Robots Modes
The smart car comes with three modes listed as the following:
1. Line Following: The car follows a dark line using greyscalor sensors, and stops when it reaches the end.
2. Manual Control: Allows the user to control the robots as a remote control car. This method is great if the robot car was used to do a specific mission that needs direct directions. It was also used during testing and debugging to help the robot get out of a spaces where he got stuck.
3. Automatic Object Avoidance: This allows the robot to navigate the space autonomously, and for a non-specified goal.


The "tunel" folder has the code of the autonoumous navigation of the car. During development this code was written and tested seperately before getting embedded with the other ones. I left it there for reference