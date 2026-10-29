# SmartCarUniPrj

This project was made by:
- Lawrence Abou Karroum (Personal Webiste: https://lawrence-abou-karroum.web.app/, linkedin: )
- Ahmad Mansour (linkedin: )
- Majd Nasrallah (linkedin: )
- Ziad hamede (linkedin: )
It was the final project in the Embedded Systems Lab course at the Univeristy of Balamand, and the goal was to achieve three modes in the project of which they were successfully made and tested. (the mode will be mentioned later on below)


This image shows the final result of the project: 30-4-2024.jpg
Check this short video showing a quick glimse of the final reuslts on my channel on youtube: https://www.youtube.com/shorts/GpCHDOonlNM

This project was done in 30-5-2024

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
This project is made of a robot and its controller. The robot is build arround the Arduino Mega, that is acting as the brain of the robot, and connects to the Arduino Uno that works as the brain of the controller, via bluetooth modules HC-05, where the module of the controller worked as a 'Master', and that of the robot car as a 'Salve'. The robot car is equipped with an ultrasonic sensor (HC-SR04) as shown in the figure below, which detect obsticals during the autonumous navigation. The drawwing of the car also shows infrared sensors, however in the application later on they were replaced by a servo motor (Tower Pro - Micro servo 9g - SG90), and the ultrasonic sensor was fixed on the rotator of the servo motor, so the servo keeps turning a 180 degrees while the ultrasonic sensor is reading distances which gives the car a full radar-like ability to detect any obstical in its front even is if it was not directly in the front. Additionally, three grey scalor sensors that detect lines with dark colors and follow it all along, the they were distributed such that the left one detects if there are any line on the left, the right one detects any line on the right, and the middle one detect a line in the middle, if none of them detected any lines, the robot consider that is reaches the end, so it stops.
The car was powered with two power sources, the motors were connected to an external power supply of lithium-ion batteries, and the arduino mega was powered through a 9V battery via its DC power jack to preserve its stability of operation.
As a special touch we've added white leds in the front and red leds in the back of the car, which helped us to easily differentiate the front from the end when the car moving away form us. As well as the buzzer, which played an important role in testing connections, as we were using the buzzer to make a sound whenever the controller successfully connects to the car, while both the buzzer and the leds served an artistic and fun touch to the project.
To allow longer test time we built the car with three levels of speed 60%, 80% and 100% which stands for nearly half the full speed that the car can reach, 80% stands for nearly most of the speed that the car can reach, and the 100% stands for the full speed that the car can reach, to explain what the "full speed that the car can reach" stands for, we have to explain how a 60% and 80% worked.

L298-H-Bridge.png

As shown in the 30-5-2024.jpg image above, you can notice a red part is the L298 H-bridge (see L298-H-Bridge.png image above), this part allowed the arduino mega form controlling the motors, by allowing the electrical energy to flow from the lithium batteries to the motors and provide a higher power for better drive, while keeping the 9V for the controller and its sensors and LEDs which required less power, and maintained stability in the system.
The microcontroller (Arduino Mega) was using Time-Width Modulation (TWM) to control the motors, so 60% means the duty cycle of the TWM was at 60% or k=0.6T (where T stands for the period of time), and 80% referes to a duty cycle of k = 0.8T (where T stands for the period of time) and for 100% k is nearly fully the same to make the transistor full conducting all the time, which allows the motors to receive maximum power.

On the other hand the controller was made out of a joy stick which is used in the manual mode to control the direction of the car. Five buttons were used in this project:
- Button one at the top is to set the mode (Automumous/Automatic, Manual, Line follower)
- Buzzer (you can notice in the image 30-5-2024.jpg that there is also a buzzer of the controller, that was added there to replicate the buzzer sound of the car, so if it was far away and you the buzzer button was pressed, the buzzer on the controller will be informing us that the buzzer is active even if we can't hear it from the car)
- One of them is to toggle lights (both the ones in the front and in the back)
- This button is to control the power reaching the motors and hence the speed of the car. It was very handy during testing to alongate the life of the battery to enable more testing time per charge.
- The last button was to "OK" or set button which allow used in cases like fetching modes.
(The process that explains why an "OK" button was needed will be explained in a little bit.)

An LCD screen was used to display information and states, and the bluetooth module for communication with the car, and a 9V battery that powers the Arduino Uno on the controller.


*How it all works*
When the car and the controller are activated, the bluetooth module immediately start scanning and looking for the slave module on the car, when they connect, the buzzer beeps indicating the connection successful. Everything in the car is off and it is set by default to manual mode.
When the mode button is clicked the LCD screen shows the autonumous mode, and if it was clicked again, it switches to the next mode which will be the line follower, at this level clicking the ok button will select the line follower as it selects the mode that is appearing on the screen, to cancel, the same current model would be reselected, as no cancel button is provided in this setup for the lack of space and resources, and for the aim of simplicity.
Also note that the yellow button on the car was primarly used for easy access to reset of the car controller (Arduino Mega)

Note: None of the products or components shown in the images above are sponsored, images are provided as is even without blurring the brand names.