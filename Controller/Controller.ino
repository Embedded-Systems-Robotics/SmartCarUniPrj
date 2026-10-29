// Note: To know more about this project, please refer to the 'About.txt' file

// Including all project files in this main file
#include "Variables.h"
#include "Functions.h"

// Creating a Bluetooth Instance
const int RX_PIN = 2;
const int TX_PIN = 3;
SoftwareSerial bluetoothSerial(RX_PIN, TX_PIN);

// Board Elements Variables
const int buzzerBt = 8;
const int lightBt = 10;
const int speedBt = 11;
const int modeBt = 12;
const int buzzerPin = 9;
const int okBt = 7;
const int test_led = 4;
const int xAxisPin = A1;
const int yAxisPin = A0;


// Defining Variables
Modes mode = MANUAL;
bool light_state = false;
bool buzzer_state = false;
int current_speed = 60;
int current_mode = 1; // Manual Mode

bool lightBt_pressed = false;
bool speedBt_pressed = false;
bool modeBt_pressed = false;
bool modeBt2_pressed = false;
bool buzzer_pressed = false;
bool okBt_pressed = false;

bool mode_loop = true;
bool break_mode = false;

bool isConnected = false;

// JoyStick Variables
int x_postion;
int y_postion;
const int error_x_axis = 50;
const int error_y_axis = 100;
char direction = 'o';

// Defining Objects
LiquidCrystal_I2C lcd(0x27,16,2);


// Setup Function
void setup() {
  Serial.begin(9600); // Setting serial communication to 9600 bit/second
  bluetoothSerial.begin(9600); // Setting bluetooth serial communication to 9600 bit/second

  // Specifying pins as i/o 
  pinMode(buzzerBt, INPUT_PULLUP);
  pinMode(lightBt, INPUT_PULLUP);
  pinMode(speedBt, INPUT_PULLUP);
  pinMode(modeBt, INPUT_PULLUP);
  pinMode(okBt, INPUT_PULLUP);
  pinMode(test_led, OUTPUT);

  // Initializing the lcd
  lcd.init();
  lcd.backlight();
  lcd.home();

  // Initializing board elements
  SetLights(false);
  current_speed = SetSpeed(100);
  SetMode(1); // Setting the mode to Manual as by default
  Alert("Connecting...");
}


// Main Loop Function
void loop() {
  // Informing the user the connection is successfully established
  if(bluetoothSerial.available()){
    if(bluetoothSerial.read()=='c'){
      if(isConnected == false){
        ClearLCD();
        Alert("Connected!");
        isConnected = true;
      }
    }
  }

  // Controlling the buzzer
  while(digitalRead(buzzerBt) == LOW){
    if(!buzzer_pressed){
      buzzer_state = true;
      SetBuzzer(buzzer_state);
    }
    buzzer_pressed = true;
    Send();
  }
  if(buzzer_state){
    buzzer_state = false;
    SetBuzzer(buzzer_state);
    buzzer_pressed = false;
  }

  // Controlling the lights
  while(digitalRead(lightBt) == LOW){
    if(!lightBt_pressed){
      light_state = !light_state;
      SetLights(light_state);
    }
    lightBt_pressed = true;
  }
  lightBt_pressed = false;

  // Controlling speed limits
  while(digitalRead(speedBt) == LOW){
    if(!speedBt_pressed){
      current_speed = SetSpeed(current_speed);
    }
    speedBt_pressed = true;
  }
  speedBt_pressed = false;

  // Changing the mode
  while(digitalRead(modeBt) == LOW){
    if(!modeBt_pressed){

      while(break_mode == false){
        while(digitalRead(modeBt) == LOW){
          if(!modeBt2_pressed){
            String full_question = "Switch to ";
            current_mode++;
            if(current_mode<=3){
              full_question += KnowingNextMode(current_mode);
              full_question += "?";
              Alert("                ");
              Alert(full_question);
            }
            else{
              current_mode = 1;
              full_question += KnowingNextMode(current_mode);
              Alert("                ");
              Alert(full_question);
            }
          }
          modeBt2_pressed = true;
        }
        modeBt2_pressed = false;

        while(digitalRead(okBt) == LOW){
          if(!okBt_pressed){
            Alert("                ");
            current_mode = ModeToInt(KnowingNextMode(current_mode));
            SetMode(current_mode);
            Serial.print("The current setted mode is: ");
            Serial.print(KnowingNextMode(current_mode));
            Serial.print(" ");
            Serial.println(current_mode);
            break_mode = true;
          }
          okBt_pressed = true;
        }
        okBt_pressed = false;
      }
    }
    modeBt_pressed = true;
    break_mode = false;
  }
  modeBt_pressed = false;

  // Making the "OK" button work as a clear button for the display
  while(digitalRead(okBt) == LOW){
    if(!okBt_pressed){
      Alert("                ");
    }
    okBt_pressed = true;
  }
  okBt_pressed = false;

  // Displaying current direction
  // Updating data 
  x_postion = analogRead(xAxisPin);
  y_postion = analogRead(yAxisPin);
  if(y_postion > 506+error_y_axis){
    if(direction != 'f'){
      direction = 'f';
      SetDirection(direction);
    }
  }
  else if(y_postion<506-error_y_axis){
    if(direction != 'b'){
      direction = 'b';
      SetDirection(direction);
    }
  }
  else if(x_postion > 501+error_x_axis){
    if(direction != 'r'){
      direction = 'r';
      SetDirection(direction);
    }
  }
  else if(x_postion<501-error_x_axis){
    if(direction != 'l'){
      direction = 'l';
      SetDirection(direction);
    }
  }
  else if(direction != 'o'){
    direction = 'o';
    SetDirection(direction);
    Serial.println(direction);
  }

  Send();
  delay(50);
}