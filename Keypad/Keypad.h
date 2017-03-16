//Shubham Patel, Will Clark, Kevin Warshaw
#ifndef KEYPAD_H
#define KEYPAD_H

#include "Button.h"
#include "Arduino.h"




class Keypad {
public:
  Keypad(int a, int b, int c, int d);
  bool isArmed();
  void isPressed();
  void changeHeader(int x);
  void checkDisarm();
  String getCode();
  String getInput();
  void setCode(String x);
  void arm();
  Button* one;
  Button* two;
  Button* three;
  Button* four;
  Button* five;
  Button* six;
  Button* seven;
  Button* eight;
  Button* nine;
  Button* zero;
  Button* asterisk;
  Button* pound;


private:
  bool status;
  String code;
  String input;
  int headerPin;

  friend class Button;
};

#endif
