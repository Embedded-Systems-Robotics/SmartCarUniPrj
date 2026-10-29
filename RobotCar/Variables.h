// Variables File

// Definig this file
#ifndef VARIABLES_H
#define VARIABLES_H
#include <Servo.h>

// Bluetooth connection
#define BTSerial Serial1

// Car Variables
/// Ultrasonic sensor pins
extern Servo S1;
extern const int trigPin;
extern const int echoPin;

/// Motor pins
extern const int IN1;
extern const int IN2;
extern const int M1pwmPin;
extern const int IN3;
extern const int IN4;
extern const int M2pwmPin;

/// Lights pins
extern const int frontLightsR;
extern const int frontLightsL;
extern const int backLightsR;
extern const int backLightsL;
extern const int buzzerPin;

// other variables
extern const int buzzerFrequency;
extern float speed;

// Manual Variables
extern String bt_input;
extern int x_value, y_value;
extern int buzzer, lights;
extern int the_mode;
extern int the_speed;

// line follower
extern const int left_sensor;
extern const int middle_sensor;
extern const int right_sensor;

extern int right_sensor_value;
extern int middle_sensor_value;
extern int left_sensor_value;

#endif