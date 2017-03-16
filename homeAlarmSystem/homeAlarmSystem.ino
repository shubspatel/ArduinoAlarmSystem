//Shubham Patel, Will Clark, Kevin Warshaw
#include <Keypad.h>
#include <Hall.h>

Keypad key(5,3,2,7);
Hall h;

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 200;

int photoResistor = A5;
int whiteLed = 11;
int redLed = A3;
int greenLed = A4;
int headerPin[3] = {4,6,8};
int headerItr = 0;
int armedClosed = 0; 
int disarmedOpen = 1;
int disarmedClosedlosed = 2;
int alarming = 3;
int state = 0;
int solenoid = 10;

void setup() {
  
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(solenoid, OUTPUT);
  pinMode(whiteLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(photoResistor, INPUT);
  key.setCode("12340");
  key.arm();
  //jammin tunes
  cli();
  TCCR1A = 0x00; //CTC mode: OCR1A determines TOP
  TCCR1B = 0x0A; //CTC mode; pre-scaler of 8
  OCR1A = 25.81; //CHANGE THIS LINE to make different tones on pin 9!!!
  DDRB |= 0x02; //Don't forget to set Arduino 9 as output!!
  sei();
  Serial.println("Arming Alarm System");
  digitalWrite(11,HIGH);
  Serial.println("System Armed");
}

void loop() {
  if (state == armedClosed) {
      int z = headerPin[headerItr];
      digitalWrite(redLed, HIGH);
      digitalWrite(whiteLed, HIGH);
      delay(2);
      key.changeHeader(z);
      digitalWrite(z, HIGH);
      key.isPressed();
      if(h.pry()) {
        Serial.println("Door pried. Enter correct code to disarm.");
        state = alarming;
        digitalWrite(z,LOW);
        digitalWrite(redLed,LOW);
      }
      digitalWrite(z, LOW);
      headerItr++;
      if (headerItr > 2) {
          headerItr = 0;
      }  
      if (digitalRead(photoResistor) == HIGH) {
        Serial.println("Trip wire detected. Enter correct code to disarm.");
        state = alarming;
        digitalWrite(redLed, LOW);
      }
      if(!key.isArmed()) {
        Serial.println("Correct code entered. Disarming system.");
        digitalWrite(z, LOW);
        digitalWrite(redLed, LOW);
        state = disarmedClosedlosed;
        digitalWrite(solenoid, HIGH);
        delay(1000);
        digitalWrite(solenoid, LOW);
      }
      digitalWrite(whiteLed, LOW);
  }
  if (state == disarmedClosedlosed) {
    digitalWrite(4, HIGH);
    digitalWrite(greenLed, HIGH);
    if (key.asterisk->checkButton()) {
      state = armedClosed;
      key.arm();
      digitalWrite(greenLed, LOW);
      digitalWrite(4, LOW);
      Serial.println("System armed.");
    }
    if (digitalRead(A2) == LOW) {
      Serial.println("Latch open.");
      state = disarmedOpen;
      delay(10);
    }
  }
  if (state == disarmedOpen) {
    digitalWrite(4, HIGH);
    digitalWrite(greenLed,HIGH);
    if (key.asterisk->checkButton()) {
      state = armedClosed;
      key.arm();
      digitalWrite(greenLed, LOW);
      digitalWrite(4, LOW);
      Serial.println("Arming system. Please close door or system will alarm.");
      digitalWrite(solenoid,HIGH);
      delay(1000);
      digitalWrite(solenoid,LOW);
    }
    if (!h.isOpen()) {
      digitalWrite(solenoid,HIGH);
      delay(1000);
      digitalWrite(solenoid,LOW);
      Serial.println("Latch closed.");
      state = disarmedClosedlosed;
    }
  }
  if (state == alarming) {
    // noise maker
    TCCR1A |= (1 << COM1A0);
    delay(5);
    TCCR1A &= ~(1 << COM1A0);
    delay(10);
    // led blink
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(redLed, ledState);
    }
    // keypad
    int z = headerPin[headerItr];
    key.changeHeader(z);
    digitalWrite(z, HIGH);
    key.isPressed();
    delay(5);
    if(!key.isArmed()) {
      Serial.println("Correct code entered. Disarming system.");
      digitalWrite(z, LOW);
      digitalWrite(redLed, LOW);
      state = disarmedOpen;
      Serial.println("Latch opened.");
      TCCR1A &= ~(1 << COM1A0);
    }
    digitalWrite(z, LOW);
    headerItr++;
    if (headerItr > 2) {
        headerItr = 0;
    }      
  }
}
