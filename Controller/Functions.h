// Fnuctions Header File

// Definig this file
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Core Code
#include <Arduino.h>
#include <Wire.h>
#include "Variables.h"

// UI Functions
void checkBluetoothConnection();
void Alert(String message);
void SetMode(int switch_mode);
void SetBuzzer(bool buzzer_state);
void BuzzISR();
void SetBuzzer(bool buzzer_state);
void SetLights(bool light_state);
int SetSpeed(int current_speed);
void RobotSpeed(int current_robot_speed);
String KnowingNextMode(int current_mode);
int ModeToInt(String stringMode);
void Send();
void SetDirection(char direction);
void ClearLCD();


// For debugging stuff
void Display(int xPosition, int yPosition);

#endif