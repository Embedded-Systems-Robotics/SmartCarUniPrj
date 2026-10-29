// Fnuctions Header File

// Definig this file
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Core Code
#include <Arduino.h>
#include <Wire.h>
// #include "LiquidCrystal_I2C.h"
#include "Variables.h"

// General Functions
void movefw(float k);
void movebw(float k);
void turnLeft(float k);
void turnRight(float k);
void stopMotors();

// Manual Mode Functions
void GetNewValues();
void TogglingLeds(bool TogglingLeds);

// Auto Mode Functions
int LookRight();
int LookLeft();
int measureDistance();


// Line Follower
void update();
void LineFollower();
void StopLineFollowing();

#endif