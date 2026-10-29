#include <Servo.h>
Servo S1;


const int trigPin = 53;
const int echoPin = 52;

int dist;
long duration;
float cm;

int currentAngle = 0; // Track the current angle of the servo
int times = 0;
bool restart = false;

const int IN1 = 22;
const int IN2 = 23;
const int M1pwmPin = 2;
const int IN3 = 24;
const int IN4 = 25;
const int M2pwmPin = 3;


bool obsticalFoundL = false;
bool obsticalFoundR = false;

int speed = 30;

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

int measureDistance(){
  delay(20);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm=duration * 0.0343 / 2.0;
  return cm;
}

void setServoAngle(int angle){
  if (angle >= 0 && angle <= 180) { // Ensure the angle is within valid range
    S1.write(angle); // Set the servo to the specified angle
  }
}


void turnServoByDegrees(int angle) {
  if (currentAngle > 180 || currentAngle < 0) {
    currentAngle = 0; // Reset the angle back to 0 after reaching 180 degrees
  }
  S1.write(currentAngle); // Set the servo to the new angle
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  S1.attach(9); // Attach the servo to pin 9

  S1.write(currentAngle);


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(M1pwmPin, OUTPUT);
  pinMode(M2pwmPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}

void obsticalAtRight(int angle){
  // int time = map(angle, 0, 180, 60, 0);
  stopMotors();
  delay(100);
  turnLeft(speed+20);
  delay(1500);
  stopMotors();
}

void obsticalAtLeft(int angle){
  // int time = map(angle, 0, 180, 60, 0);
  stopMotors();
  delay(100);
  turnRight(speed+20);
  delay(1500);
  stopMotors();
}

void AvoidObstical(int angle){
  if(angle > 90){
    turnRight(60);
    delay(800);
    stopMotors();
    delay(80);
  }
  else{
    turnLeft(60);
    delay(800);
    stopMotors();
    delay(80);
  }
}


void Scan(){
  currentAngle = 0;
  S1.write(currentAngle);

  times = 0;
  if(restart == false){
    for(int i=0; i<=36; i++){
      currentAngle = i*5;
      turnServoByDegrees(currentAngle);
      Serial.println(currentAngle);
      dist = measureDistance();
      if(dist < 11){
        if(times > 2){
          obsticalFoundL = true;
          AvoidObstical(currentAngle);
          times = 0;
          restart = true;
          break;
        }
        times++;
      }
    }
  }

  if(restart == false){
    for(int i=36; i>0; i--){
      currentAngle = i*5;
      turnServoByDegrees(currentAngle);
      Serial.println(currentAngle);
      dist = measureDistance();
      if(dist < 11){
        if(times > 2){
          obsticalFoundR = true;
          AvoidObstical(currentAngle);
          times = 0;
          restart = true;
        }
        times++;
      }
    }
  }
}


void loop() {
  // currentAngle = 0;
  // S1.write(currentAngle); // setting the beginning angle

  // moving
  movefw(speed);
  restart = false; // reset the restart
  Scan();
  

  
}

