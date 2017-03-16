//Shubham Patel, Will Clark, Kevin Warshaw
#include "Hall.h"

Hall::Hall() {
}

bool Hall::pry() { //ARMED
	pinMode(A2, INPUT);
	if(digitalRead(A2) == LOW) { //assuming HIGH reading when closed
		return true;
	}
	return false;
}


bool Hall::isOpen() {
	if (digitalRead(A2) == HIGH){
		return false;
	}
	return true;
}
