// Requires Arduino Joystick Library https://github.com/MHeironimus/ArduinoJoystickLibrary
#include <Joystick.h>
#include <Adafruit_PCF8574.h>
#include <Wire.h>

Adafruit_PCF8574 expander_01;
//Adafruit_PCF8574 expander_02;

Joystick_ Joystick;

int currentButtonState0;
int lastButtonState0;
int currentButtonState1;
int lastButtonState1;
int currentButtonState2;
int lastButtonState2;
int currentButtonState3;
int lastButtonState3;
int currentButtonState4;
int lastButtonState4;
int currentButtonState5;
int lastButtonState5;
int currentButtonState6;
int lastButtonState6;
int currentButtonState7;
int lastButtonState7;

int currentButtonState10;
int lastButtonState10;
int currentButtonState11;
int lastButtonState11;
int currentButtonState12;
int lastButtonState12;

int currentButtonState21;
int lastButtonState21;

const int buttonPin2 = 0;
const int buttonPin5 = 5;

int JoystickX;
int JoystickY;
int JoystickZ;
int Throttle;

void setup() {
  Serial.begin(115200);
  expander_01.begin(0x21);
  //expander_02.begin(0x27);
  expander_01.pinMode(0, INPUT_PULLUP);
  expander_01.pinMode(1, INPUT_PULLUP);
  expander_01.pinMode(2, INPUT_PULLUP);
  expander_01.pinMode(3, INPUT_PULLUP);
  expander_01.pinMode(4, INPUT_PULLUP);
  expander_01.pinMode(5, INPUT_PULLUP);
  expander_01.pinMode(6, INPUT_PULLUP);
  expander_01.pinMode(7, INPUT_PULLUP);

  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin5, INPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  

// Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(0, 1024); 
  Joystick.setYAxisRange(0, 1024);
  Joystick.setZAxisRange(0, 1024);
  Joystick.setThrottleRange(0, 1024);
}

void loop() {

// Read Joystick
  JoystickX = analogRead(A1); // Hall effect sensor connects to this analog pin
  JoystickY = analogRead(A0); // Hall effect sensor connects to this analog pin
  JoystickZ = analogRead(A8);
  Throttle  = analogRead(A9); // Hall effect sensor connects to this analog pin

  int currentButtonState0 = expander_01.digitalRead(0); // Button 0
    if (currentButtonState0 != lastButtonState0)
    {
    Joystick.setButton(0, currentButtonState0);
    lastButtonState0 = currentButtonState0;
  }

  int currentButtonState1 = expander_01.digitalRead(1); // Button 1
    if (currentButtonState1 != lastButtonState1)
    {
    Joystick.setButton(1, currentButtonState1);
    lastButtonState1 = currentButtonState1;
  }

  int currentButtonState2 = expander_01.digitalRead(2); // Button 2
    if (currentButtonState2 != lastButtonState2)
    {
    Joystick.setButton(2, currentButtonState2);
    lastButtonState2 = currentButtonState2;
  }

  int currentButtonState3 = expander_01.digitalRead(3); // Button 3
    if (currentButtonState3 != lastButtonState3)
    {
    Joystick.setButton(3, currentButtonState3);
    lastButtonState3 = currentButtonState3;
  }

  int currentButtonState4 = expander_01.digitalRead(4); // Button 4
    if (currentButtonState4 != lastButtonState4)
    {
    Joystick.setButton(4, currentButtonState4);
    lastButtonState4 = currentButtonState4;
  }

  int currentButtonState5 = expander_01.digitalRead(5); // Button 5
    if (currentButtonState5 != lastButtonState5)
    {
    Joystick.setButton(5, currentButtonState5);
    lastButtonState5 = currentButtonState5;
  }

  int currentButtonState6 = expander_01.digitalRead(6); // Button 6
    if (currentButtonState6 != lastButtonState6)
    {
    Joystick.setButton(6, currentButtonState6);
    lastButtonState6 = currentButtonState6;
  }
  /*
  int currentButtonState7 = expander_01.digitalRead(7); // Button 7
    if (currentButtonState7 != lastButtonState7)
    {
    Joystick.setButton(7, currentButtonState7);
    lastButtonState7 = currentButtonState7;
  }
  */
  int currentButtonState11 = digitalRead(buttonPin5); // Button 11
    if (currentButtonState11 != lastButtonState11)
    {
    Joystick.setButton(11, currentButtonState11);
    lastButtonState11 = currentButtonState11;
  }
  /*
  int currentButtonState21 = digitalRead(buttonPin2); // Button 21
    if (currentButtonState21 != lastButtonState21)
    {
    Joystick.setButton(21, currentButtonState21);
    lastButtonState21 = currentButtonState21;
  }
  */
  Joystick.setXAxis(JoystickX);
  Joystick.setYAxis(JoystickY);
  Joystick.setZAxis(JoystickZ);
  Joystick.setThrottle(Throttle);
  Joystick.sendState();

}