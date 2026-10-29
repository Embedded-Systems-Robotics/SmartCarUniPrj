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


The "tunel" folder has the code of the autonoumous navigation of the car. During development this code was written and tested seperately before getting embedded with the other ones. I left it there for reference.


Details:
This project is made of a robot and its controller. The robot is build arround the Arduino Mega, that is acting as the brain of the robot, and connects to the Arduino Uno that works as the brain of the controller, via bluetooth modules HC-05, where the module of the controller worked as a 'Master', and that of the robot car as a 'Salve'. The robot car is equipped with an ultrasonic sensor as shown in the figure below, which detect obsticals during the autonumous navigation, as well with three grey scalor sensors that detect lines with dark colors and follow it all along, the they were distributed such that the left one detects if there are any line on the left, the right one detects any line on the right, and the middle one detect a line in the middle, if none of them detected any lines, the robot consider that is reaches the end, so it stops.
The car was powered with two power sources, the motors were connected to an external power supply of lithium-ion batteries, and the arduino mega was powered through a 9V battery via its DC power jack to preserve its stability of operation.
As a special touch we've added white leds