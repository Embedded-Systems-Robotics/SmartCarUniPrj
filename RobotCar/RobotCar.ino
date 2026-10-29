// See File "About.txt" to know more about this project

// Including Files
#include "Variables.h"
#include "Functions.h"

// Motor variables
const int IN1 = 22;
const int IN2 = 23;
const int M1pwmPin = 2;
const int IN3 = 24;
const int IN4 = 25;
const int M2pwmPin = 3;

// LEDs and Buzzer pins
const int frontLightsR = 50;
const int frontLightsL = 48;
const int backLightsR = 27;
const int backLightsL = 26;
const int buzzerPin = 28;

// Ultrasonic Sensor variables
const int trigPin = 53;
const int echoPin = 52;
int ObstacleDistance = 20;
int distance;

// Servo variables
int ServoPin = 9;
Servo S1;

// Manual Variables
float speed = 80;
const int buzzerFrequency = 415;

String bt_input;
int x_value;
int y_value;
String part1, part2, part3, part4, part5;
const int error_x_axis = 45;
const int error_y_axis = 30;
int controller_speed;
float speed_per;
float result;
int buzzer, lights;
int the_mode = 1;
int the_speed;
bool leds_state = false;
bool buzzer_state = false;

int distanceL;
int distanceR;

// line follower
const int left_sensor = 40;
const int middle_sensor = 41;
const int right_sensor = 42;

int right_sensor_value;
int middle_sensor_value;
int left_sensor_value;

int sync = 0;

// Setup function
void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  // Associating i/o to pins
  /// Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(M1pwmPin, OUTPUT);
  pinMode(M2pwmPin, OUTPUT);

  /// others pins
  pinMode(frontLightsR, OUTPUT);
  pinMode(frontLightsL, OUTPUT);
  pinMode(backLightsR, OUTPUT);
  pinMode(backLightsL, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Servo & Ultrasonic Sensor i/o pins
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  S1.attach(ServoPin);
  digitalWrite(13, LOW);

  // Line Following
  pinMode(left_sensor, INPUT);
  pinMode(middle_sensor, INPUT);
  pinMode(right_sensor, INPUT);
}


void loop() {
  if (BTSerial.available()) {
    // Updating the values
    GetNewValues();

    // Sending a message that the connection still estalblished
    BTSerial.write('c');

    // Manual Mode
    if(the_mode == 1){
      // Serial.println(the_mode);
      // Updating Car Speed
      if(the_speed != speed){
        if(the_speed == 100){
          speed = 90;  
        }
        else{
          speed = the_speed;
        }
      }

      // Toggiling LEDs
      if(lights == 1 && !leds_state){
        leds_state = true;
        TogglingLeds(leds_state);
      }
      else if(leds_state && lights==0){
        leds_state = false;
        TogglingLeds(leds_state);
      }

      // Buzzer
      if(buzzer == 1 && !buzzer_state){
        tone(buzzerPin, buzzerFrequency);
        buzzer_state = true;
      }
      else if(buzzer_state && buzzer == 0){
        noTone(buzzerPin);
        buzzer_state = false;
      }

      // Manual Controll
      if(y_value > 506+error_y_axis){
        movefw(speed);
      }
      else if(y_value<506-error_y_axis){
        movebw(speed);
      }
      else if(x_value > 501+error_x_axis){
        turnRight(speed);
      }
      else if(x_value<501-error_x_axis){
        turnLeft(speed);
      }
      else{
        stopMotors();
      }
    } // Manual Mode 

    // Auto Mode
    else if(the_mode == 2){
      distance=measureDistance();
      delay(40);
      if(distance<=ObstacleDistance){
        stopMotors();
        delay(100);
        distanceR=LookRight();
        delay(200);
        distanceL=LookLeft();
        delay(200);
        if(distanceR>distanceL){
          while(distance<ObstacleDistance){
          turnRight(speed);
          distance=measureDistance();
          }
          if(distance>ObstacleDistance){
          stopMotors();
          delay(200);
          }

        }
        else if(distanceR<distanceL){
          while(distance<ObstacleDistance){
          turnLeft(speed);
          distance=measureDistance();
          }
          if(distance>ObstacleDistance){
          stopMotors();
          delay(200);
          }
        }
        
      }
      else{
        movefw(speed);
      }

      // Toggiling LEDs
      if(lights == 1 && !leds_state){
        leds_state = true;
        TogglingLeds(leds_state);
      }
      else if(leds_state && lights==0){
        leds_state = false;
        TogglingLeds(leds_state);
      }
    }

    // Line Following Mode
    else if(the_mode == 3){
      speed = 60;
      distance = measureDistance();
      delay(40);
      if(distance < ObstacleDistance){
        stopMotors();
        digitalWrite(backLightsR, HIGH);
        digitalWrite(backLightsL, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(350);
        digitalWrite(buzzerPin, LOW);
        delay(350); 
      }
      else{
        LineFollower();
      }
    }
  } // Ending if BT connection


} // Ending the loop
