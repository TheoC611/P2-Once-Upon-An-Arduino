#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

const int ledPin1 = 11;
const int ledPin2 = 12;
const int ledPin3 = 13;

unsigned long currentTime;
unsigned long previousTime = 0;
int timerLength = 100;
bool ledOn = false;

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

unsigned long servo1StartTime = 0;
unsigned long servo3StartTime = 0;
bool servo1Active = false;
bool servo3Active = false;

void setup() {
  myservo1.attach(7);
  myservo2.attach(8);
  myservo3.attach(9);
  myservo4.attach(10);

  myservo1.write(360);
  servo1Active = true;
  servo1StartTime = millis();

  myservo3.write(360);
  servo3Active = true;
  servo3StartTime = millis();

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonAPin, INPUT);
  pinMode(buttonBPin, INPUT);
  pinMode(buttonCPin, INPUT);
  pinMode(buttonDPin, INPUT);
  pinMode(buttonEPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  currentTime = millis();

  buttonAState = digitalRead(buttonAPin);

  if (buttonAState != lastButtonAState && A == false) {
    if (buttonAState == HIGH) {
      if (currentTime - previousTime > timerLength) {
        ledOn = !ledOn;
        previousTime = currentTime;
      }

      if (ledOn) {
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
      } else {
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
      }
      A = true;
    }
  }

  if (A == true) {
    buttonBState = digitalRead(buttonBPin);
    if (buttonBState != lastButtonBState && B == false) {
      if (buttonBState == HIGH) {
        myservo1.write(360);
        servo1Active = true;
        servo1StartTime = currentTime;
        B = true;
      }
    }
  }

  if (servo1Active && (currentTime - servo1StartTime >= 333)) {
    myservo1.write(90);
    servo1Active = false;
  }

  if (B == true) {
    buttonCState = digitalRead(buttonCPin);
    if (buttonCState != lastButtonCState && C == false) {
      if (buttonCState == HIGH) {
        myservo2.write(180);
        C = true;
      }
    }
  }

  if (C == true) {
    buttonDState = digitalRead(buttonDPin);
    if (buttonDState != lastButtonDState && D == false) {
      if (buttonDState == HIGH) {
        myservo3.write(360);
        servo3Active = true;
        servo3StartTime = currentTime;
        D = true;
      }
    }
  }

  if (servo3Active && (currentTime - servo3StartTime >= 333)) {
    myservo3.write(90);
    servo3Active = false;
  }

  if (D == true) {
    buttonEState = digitalRead(buttonEPin);
    if (buttonEState != lastButtonEState && E == false) {
      if (buttonEState == HIGH) {
        myservo4.write(180);
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
