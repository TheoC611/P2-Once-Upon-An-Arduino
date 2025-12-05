/*
Raiders of the Lost Ark

Team Name: Team TNT
Team Members: Noah Rutledge and Theo Chau
Description: In this program, there are five interactions that tell the story of Raiders of the Lost Ark.
*/

//include the servo library
#include <Servo.h>

//create four servo objects
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

//LED pin assignments
const int ledPin1 = 11;
const int ledPin2 = 12;

//timing variables for LED toggling
unsigned long currentTime;
unsigned long previousTime = 0;
int timerLength = 100;
bool systemOn = false;
bool ledOn = false;

//button A variables
const int buttonAPin = 2;
int buttonAState = 0;
int lastButtonAState = 0;
bool A = false;

//button B variables
const int buttonBPin = 3;
int buttonBState = 0;
int lastButtonBState = 0;
bool B = false;

//button C variables
const int buttonCPin = 4;
int buttonCState = 0;
int lastButtonCState = 0;
bool C = false;

//button D variables
const int buttonDPin = 5;
int buttonDState = 0;
int lastButtonDState = 0;
bool D = false;

//button E variables
const int buttonEPin = 6;
int buttonEState = 0;
int lastButtonEState = 0;
bool E = false;

//servo timing for timed motion
unsigned long servo1StartTime = 0;
unsigned long servo3StartTime = 0;
bool servo1Active = false;
bool servo3Active = false;

void setup() {
  //attach servos to pins
  myservo1.attach(7);
  myservo2.attach(8);
  myservo3.attach(9);
  myservo4.attach(10);

  //start servo 1 with a rotation and start timer
  myservo1.write(360);
  servo1Active = true;
  servo1StartTime = millis();

  //start servo 3 with a rotation and start timer
  myservo3.write(360);
  servo3Active = true;
  servo3StartTime = millis();

  //set LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  //set button pins as inputs
  pinMode(buttonAPin, INPUT);
  pinMode(buttonBPin, INPUT);
  pinMode(buttonCPin, INPUT);
  pinMode(buttonDPin, INPUT);
  pinMode(buttonEPin, INPUT);

  //begin serial communication
  Serial.begin(9600);
}

void loop() {
  //get current time
  currentTime = millis();

  //button A: LED toggle
  buttonAState = digitalRead(buttonAPin);

  if (buttonAState != lastButtonAState && A == false) {
    if (buttonAState == HIGH) {
      systemOn = true;
      A = true;
    }
  }

  //if LED system is active, blink LEDs at the preset interval
  if (systemOn == true) {
    //basic toggling timer
    if (currentTime - previousTime > timerLength) {
      ledOn = !ledOn;
      previousTime = currentTime;
    }

    //update LED outputs
    if (ledOn) {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
    } else {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
    }
  }

  //button B: move servo 1
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

  //stop servo 1 after 180 degree rotation
  if (servo1Active && (currentTime - servo1StartTime >= 333)) {
    myservo1.write(90);
    servo1Active = false;
  }

  //button C: move servo 2
  if (B == true) {
    buttonCState = digitalRead(buttonCPin);
    if (buttonCState != lastButtonCState && C == false) {
      if (buttonCState == HIGH) {
        myservo2.write(180);
        C = true;
      }
    }
  }

  //button D: move servo 3
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

  //stop servo 3 after 180 degree rotation
  if (servo3Active && (currentTime - servo3StartTime >= 333)) {
    myservo3.write(90);
    servo3Active = false;
  }

  //button E: move servo 4
  if (D == true) {
    buttonEState = digitalRead(buttonEPin);
    if (buttonEState != lastButtonEState && E == false) {
      if (buttonEState == HIGH) {
        myservo4.write(180);
        E = true;
      }
    }
  }

  //when everything is done
  if (E == true) {
    Serial.println("The End!");
  }

  //update last states for all buttons
  lastButtonAState = buttonAState;
  lastButtonBState = buttonBState;
  lastButtonCState = buttonCState;
  lastButtonDState = buttonDState;
  lastButtonEState = buttonEState;
}
