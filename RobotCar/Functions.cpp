// Functions File

// Including needed libraries
#include "Functions.h"
#include "Variables.h"

// General Functions (for all modes):
//-----------------------------------

// Function for moving Forward
void movefw(float k){
  float DutyCycle = map(k, 0, 100, 0, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(M1pwmPin, DutyCycle);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(M2pwmPin, DutyCycle);
}

// Function for moving Backward
void movebw(float k){
  float DutyCycle = map(k, 0, 100, 0, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(M1pwmPin, DutyCycle);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(M2pwmPin, DutyCycle);
}

// Function for turning Left
void turnLeft(float k){
  float DutyCycle = map(k, 0, 100, 0, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(M1pwmPin, DutyCycle);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
  analogWrite(M2pwmPin, DutyCycle);
}

// Function for turning Right
void turnRight(float k){
  float DutyCycle = map(k, 0, 100, 0, 255);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1, LOW);
  analogWrite(M1pwmPin, DutyCycle);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(M2pwmPin, DutyCycle);
}

// Function for stopping motors
void stopMotors(){
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(M1pwmPin, 0);
  analogWrite(M2pwmPin, 0);
}

// Manual Mode Fnuctions:
//-----------------------
// Receiving new values from the bluetooth module and updating the variables
void GetNewValues(){
  bt_input = BTSerial.readStringUntil('\n');

  // Serial.println(bt_input); // For debugging

  // Find delimiter positions
  int delimiterIndex1 = bt_input.indexOf('|');
  int delimiterIndex2 = bt_input.indexOf('$');
  int delimiterIndex3 = bt_input.indexOf('@');
  int delimiterIndex4 = bt_input.indexOf('#');
  int delimiterIndex5 = bt_input.indexOf('~');

  // Extract parts
  String part1 = bt_input.substring(0, delimiterIndex1);
  String part2 = bt_input.substring(delimiterIndex1 + 1, delimiterIndex2);
  String part3 = bt_input.substring(delimiterIndex2 + 1, delimiterIndex3);
  String part4 = bt_input.substring(delimiterIndex3 + 1, delimiterIndex4);
  String part5 = bt_input.substring(delimiterIndex4 + 1, delimiterIndex5);
  String part6 = bt_input.substring(delimiterIndex5 + 1);

  // Convert parts to integers
  x_value = part1.toInt();
  y_value = part2.toInt();
  buzzer = part3.toInt();
  lights = part4.toInt();
  the_mode = part5.toInt();
  the_speed = part6.toInt();
}

void TogglingLeds(bool TogglingLeds){
  if(TogglingLeds){
    digitalWrite(frontLightsL, HIGH);
    digitalWrite(frontLightsR, HIGH);
    digitalWrite(backLightsR, HIGH);
    digitalWrite(backLightsL, HIGH);
  }
  else{
    digitalWrite(frontLightsL,LOW);
    digitalWrite(frontLightsR,LOW);
    digitalWrite(backLightsR,LOW);
    digitalWrite(backLightsL,LOW);
  }
}


// Automatic Mode Functions
// -------------------------
int LookRight(){
  S1.write(0);
  delay(500);
  int distance=measureDistance();
  S1.write(90);
  return distance;
}
int LookLeft(){
  S1.write(180);
  delay(500);
  int distance=measureDistance();
  S1.write(90);
  return distance;
}

// A funtion that make the ultrasonic sensor measure the distance and return it
int measureDistance() {
  long duration;
  float cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm=duration * 0.0343 / 2.0;
  return cm;
}


// Line Following Mode Functions:
// ------------------------------
void update(){
  right_sensor_value = digitalRead(right_sensor);
  middle_sensor_value = digitalRead(middle_sensor);
  left_sensor_value = digitalRead(left_sensor);
}

// The line follower main function
void LineFollower(){
  update();
  digitalWrite(backLightsR, LOW);
  digitalWrite(backLightsL, LOW);
  if(middle_sensor_value == 0){
    while(middle_sensor_value==0){
      movefw(speed);
      update();
    }
  }
  else{
    stopMotors();
    if(left_sensor_value==0){
      while(middle_sensor_value == 1){
        turnLeft(speed);
        update();
      }
    }
    if(right_sensor_value==0){
      while(middle_sensor_value == 1){
        turnRight(speed);
        update();
      }
    }
  }
}

// The function that is done when something interrupt the path of the car
void StopLineFollowing(){
 stopMotors();
 digitalWrite(backLightsR, HIGH);
 digitalWrite(backLightsL, HIGH);

  for (int i = 0; i < 2; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(350);
      digitalWrite(buzzerPin, LOW);
      delay(350); 
    }
}
