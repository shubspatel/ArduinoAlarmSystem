//Shubham Patel, Will Clark, Kevin Warshaw
#include "Keypad.h"
#include "Button.h"
#include <Arduino.h>

Keypad::Keypad(int x, int y, int z, int a) {
  bool status = true;
  String code = "1234";
  String input = "";
  int headerPin = 4;
  one = new Button(x);
  two  = new Button(x);
  three = new Button(x);
  four = new Button(y);
  five = new Button(y);
  six =  new Button(y);
  seven = new Button(z);
  eight = new Button(z);
  nine = new Button(z);
  zero = new Button(a);
  asterisk = new Button(a);
  pound = new Button(a);
}

void Keypad::changeHeader(int x) {
  headerPin = x;
  return;
}

bool Keypad::isArmed() {
  return status;
}

void Keypad::setCode(String x) {
  code = x;
}

String Keypad::getCode() {
  return code;
}

String Keypad::getInput() {
  return input;
}

void Keypad::arm() {
  status = true;
}

void Keypad::isPressed() {
  if (headerPin == 4) {
    if (one->checkButton()){
      input += "1";
    }
    if (four->checkButton()){
      input += "4";
    }
    if (seven->checkButton()){
      input += "7";
    }
    if (asterisk->checkButton()){
      input = "";
      status = true;
    }
  }
  if (headerPin == 8) {
    if (two->checkButton()){
      input += "2";
    }
    if (five->checkButton()){
      input += "5";
    }
    if (eight->checkButton()){
      input += "8";
    }
    if (zero->checkButton()){
      input += "0";
    }
  }
  if (headerPin == 6) {
    if (three->checkButton()){
    input += "3";
    }
    if (six->checkButton()){
      input += "6";
    }
    if (nine->checkButton()){
    input += "9";
    }
    if (pound->checkButton()){
      checkDisarm();
    }
  }
}

void Keypad::checkDisarm() {
  if (code == input) {
    status = false;
  }
  input = "";
}
