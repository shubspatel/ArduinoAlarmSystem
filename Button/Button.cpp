#include <Arduino.h>
#include <Button.h>


Button::Button(int pin){ //constructor
	/*
	 * Stores pin to which button is connected
	 * Sets pinMode appropriately
	 * https://www.arduino.cc/en/Tutorial/Button
	 *
	 */
	 buttonPin = pin;
	 pinMode(pin, INPUT);
	 lastButtonState = digitalRead(buttonPin);
  }



bool Button:: checkButton(void){
//check if button pressed,
//incl. basic debouncing w/ delay()

	int currentState = digitalRead(buttonPin); //read pin

	if(currentState!= lastButtonState){
		delay(10);
		if(digitalRead(buttonPin) == LOW){
			lastButtonState = LOW; //update
			//currentState = LOW;//wait
			return true; // return that it is pressed.
		}
		lastButtonState = digitalRead(buttonPin);
	}
	return (false);


  }
