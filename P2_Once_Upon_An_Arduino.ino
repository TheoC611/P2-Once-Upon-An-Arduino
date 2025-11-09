#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

const int buttonAPin = 2;
int buttonAState = 0;
int lastButtonAState = 0;
bool A = false;

const int buttonBPin = 3;
int buttonBState = 0;
int lastButtonBState = 0;
bool B = false;

const int buttonCPin = 4;
int buttonCState = 0;
int lastButtonCState = 0;
bool C = false;

const int buttonDPin = 5;
int buttonDState = 0;
int lastButtonDState = 0;
bool D = false;

const int buttonEPin = 6;
int buttonEState = 0;
int lastButtonEState = 0;
bool E = false;

void setup() {
  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
  myservo4.attach(12);
  pinMode(buttonAPin, INPUT);
  pinMode(buttonBPin, INPUT);
  pinMode(buttonCPin, INPUT);
  pinMode(buttonDPin, INPUT);
  pinMode(buttonEPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonAState = digitalRead(buttonAPin);

  if (buttonAState != lastButtonAState) {
    if (buttonAState == HIGH) {
      A = true;
    }
  }

  if (A == true) {
    buttonBState = digitalRead(buttonBPin);
    if (buttonBState != lastButtonBState) {
      if (buttonBState == HIGH) {
        myservo1.write(180);
        B = true;
      }
    }
  }

  if (B == true) {
    buttonCState = digitalRead(buttonCPin);
    if (buttonCState != lastButtonCState) {
      if (buttonCState == HIGH) {
        myservo2.write(90);
        C = true;
      }
    }
  }

  if (C == true) {
    buttonDState = digitalRead(buttonDPin);
    if (buttonDState != lastButtonDState) {
      if (buttonDState == HIGH) {
        myservo3.write(180);
        D = true;
      }
    }
  }

  if (D == true) {
    buttonEState = digitalRead(buttonEPin);
    if (buttonEState != lastButtonEState) {
      if (buttonEState == HIGH) {
        myservo4.write(90);
        E = true;
      }
    }
  }

  if (E == true) {
    Serial.println("The End!");
  }

  lastButtonAState = buttonAState;
  lastButtonBState = buttonBState;
  lastButtonCState = buttonCState;
  lastButtonDState = buttonDState;
  lastButtonEState = buttonEState;
}
