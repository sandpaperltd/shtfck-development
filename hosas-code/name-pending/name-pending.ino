#include <iostream>
#include <stdio.h>
#include <Wire.h>

int grip_address = 0x20; // Address for the I2C expander
int status;
const int buttons_qty = 14; // >>Number<< of buttons, lower than table size due to loop behaviour

void setup() {
  // I2C
  Wire.begin();
  Serial.begin(9600);
  Wire.beginTransmission(grip_address);
  Wire.write(0);
  Wire.write(0);
  Wire.endTransmission();

  // Joystick update state
  Joystick.useManualSend(true);
}

void loop() {
  int previous_button_status[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Button status table
  Joystick.X(analogRead(8)); // Pitch axis
  Joystick.Y(analogRead(7)); // Roll axis
  //Joystick.Z(analogRead(9));

  Joystick.Zrotate(analogRead(11)); // Broken yaw axis
  Joystick.sliderLeft(analogRead(12)); // Throttle

  Wire.requestFrom(grip_address, 1); // Requisting one byte of information from the I2C expander
  while(Wire.available()){
    status = Wire.read(); // Transfering that byte into variable
  }
  
  // The >>funny<< part
  int current_button_state = 0; // Status of button that is currently, in the loop, being tested
  // Checking every button of the array
  for(int i = 0; i <= buttons_qty; i++){
    // If the button is pressed, the status is true
    // The byte can be interpreted as binary - 00001000, but also as a regular number - 8
    // By comparing the power of 2 values with status we can check if e. g. third button is pressed, by comparing it with status value
    if(status == pow(2, i)){
      current_button_state = 1;
    }
    // If not we can proceed forward, button is not pressed
    else if(status != pow(2, i)){
      current_button_state = 0;
    }

    // It would be possible to optimize this code by moving this loop inside the first loop
    // But here, if the current status of the button is different that the previous one
    // So the button changed it's position from pressed to released
    // Or the other way around
    // We can update the status of the button, and after that change it's status once again

    // So if the current status is released, but the previous was pressed
    // We update the button, and change it's status to the current, correct one
    if(current_button_state != previous_button_status[i])
    {
      Joystick.button(i + 1, 1);
      previous_button_status[i] = current_button_state;
      status = 0;
    }
  }

  Joystick.send_now(); // Updating the button state and clearing the status of whole set in the next loop
  for(int j = 0; j <= buttons_qty; j++){
    Joystick.button(j, 0);
  }
}
