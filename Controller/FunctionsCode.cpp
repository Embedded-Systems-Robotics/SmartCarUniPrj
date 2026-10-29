// Functions File

// Including needed libraries
#include "Functions.h"
#include "Variables.h"
#include <Wire.h>

// Clearing the LCD
void ClearLCD(){
  lcd.setCursor(1, 0);
  lcd.print("                ");
}

// Alert message for the LCD display
void Alert(String message){
  lcd.setCursor(1, 0);
  lcd.print(message);  
}

// To now what the next mode would be
String KnowingNextMode(int current_mode){
  switch(current_mode){
    case 1: // MANUAL
      return "Manual";
      break;
    case 2: // AUTO
      return "Auto";
      break;
    case 3: // LINE_FOLLOWER
      return "Line Following";
      break;
  }
}

// Turning the mode from string to its representitive integer
int ModeToInt(String stringMode){
  if(stringMode == "Manual"){
    return 1;
  }
  else if(stringMode == "Auto"){
    return 2;
  }
  else if(stringMode == "Line Following"){
    return 3;
  }
}

// Setting the mode
void SetMode(int switch_mode){
  lcd.setCursor(0, 8);
  switch(switch_mode){
    case 1: // MANUAL
      lcd.print("M");
      mode = MANUAL;
      direction = ' ';
      break;
    case 2: // AUTO
      lcd.print("A");
      mode = AUTO;
      direction = 'o';
      break;
    case 3: // LINE_FOLLOWER
      lcd.print("L");
      mode = LINE_FOLLOWER;
      direction = 'o';
      break;
  }
}

// Turning on the buzzer (beeping / stop beeping)
void SetBuzzer(bool buzzer_state){
  lcd.setCursor(0, 9);
  if(buzzer_state){
    lcd.print("B");
    tone(buzzerPin,440); //360
  }
  else{
    lcd.print(" ");
    noTone(buzzerPin);
  }
}

// Toggling the indicator light
void SetLights(bool light_state){
  lcd.setCursor(0, 10);
  if(light_state){
    lcd.print("L");
    digitalWrite(4, HIGH);
  }
  else{
    lcd.print(" ");
    digitalWrite(4, LOW);
  }
}

// Changing the speed
int SetSpeed(int current_speed){
  int new_speed;
  switch(current_speed){
    case 60: // 60% is power saving mode
      new_speed = 80;
      break;
    case 80: // 80% is high speed
      new_speed = 100;
      break;
    case 100: // 100% is Nitro
      new_speed = 60;
      break;
  }
  // displaying the new speed
  lcd.setCursor(0, 11);
  lcd.print("P");
  lcd.print("    "); // reset the space
  lcd.setCursor(0, 12);
  lcd.print(new_speed);
  lcd.print("%");

  return new_speed;
}

// Displaying the current position given by the Joystick (Generally Used For debugging)
void Display(int xPosition, int yPosition){
  lcd.setCursor(1, 2);
  lcd.print("             ");
  lcd.setCursor(1, 2);
  lcd.print("x=");
  lcd.print(xPosition);
  lcd.print(" y=");
  lcd.print(yPosition);
}

// Displaying the current direction on the controller LCD
void SetDirection(char dir){
  lcd.setCursor(0, 0);
  lcd.print("        ");
  lcd.setCursor(0, 0);
  switch(dir){
    case 'f':
      lcd.print("Forward");
      break;
    case 'b':
      lcd.print("Backawrd");
      break;
    case 'l':
      lcd.print("Left");
      break;
    case 'r':
      lcd.print("Right");
      break;
    case 'o':
      lcd.print("        ");
      break;
  }
}

void Send(){
  // Sending data
  bluetoothSerial.print(x_postion);
  bluetoothSerial.print("|");
  bluetoothSerial.print(y_postion);
  bluetoothSerial.print("$");
  bluetoothSerial.print(buzzer_state);
  bluetoothSerial.print("@");
  bluetoothSerial.print(light_state);
  bluetoothSerial.print("#");
  bluetoothSerial.print(current_mode);
  bluetoothSerial.print("~");
  bluetoothSerial.println(current_speed);

  // // For testing (debugging) 
  // Serial.print(x_postion);
  // Serial.print("|");
  // Serial.print(y_postion);
  // Serial.print("$");
  // Serial.print(buzzer_state);
  // Serial.print("@");
  // Serial.print(light_state);
  // Serial.print("#");
  // Serial.print(current_mode);
  // Serial.print("~");
  // Serial.println(current_speed);
}
