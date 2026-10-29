// Variables File

// Definig this file
#ifndef VARIABLES_H
#define VARIABLES_H

// UI variables
#include "LiquidCrystal_I2C.h"
extern LiquidCrystal_I2C lcd;

// Bluetooth object
#include <SoftwareSerial.h>
extern SoftwareSerial bluetoothSerial;

// Buttons' Pins
extern const int xAxisPin;
extern const int yAxisPin;
extern const int buzzerBt;
extern const int lightBt;
extern const int powerBt;
extern const int modeBt;
extern const int okBt;
extern const int buzzerPin;

// Variables for the element state
enum Modes {
  MANUAL,
  AUTO,
  LINE_FOLLOWER
};

extern Modes mode;
extern bool buzzer_state;
extern bool light_state;
extern int current_speed;
extern int current_mode;

extern bool lightBt_pressed;
extern bool speedBt_pressed;
extern bool modeBt_pressed;
extern bool modeBt2_pressed;
extern bool buzzer_pressed;
extern bool okBt_pressed;

extern bool mode_loop;
extern bool break_mode;

// JoyStick Variables
extern int x_postion;
extern int y_postion;
extern const int error_x_axis;
extern const int error_y_axis;
extern char direction;
extern const int xAxisPin;
extern const int yAxisPin;

#endif