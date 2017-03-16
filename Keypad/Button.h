//Shubham Patel, Will Clark, Kevin Warshaw
#ifndef Button_h
#define Button_h
#include <Arduino.h>
class Button
{
  private:
		int buttonPin;
		int lastButtonState;
  public:
	bool checkButton(void); //checks whether button has been pressed
	Button(const int b); //
	friend class Keypad;
  };
#endif