/*
  Motion Sensing Fly Trap
  by Matt Nutsch
  Move a servo motor when motion is detected.
*/

#include <Servo.h> 

int motionPin = 5;
int servoPin = 4;
int motionValue;
bool motionState = false; // We start with no motion detected.
bool servoMoved = false; // We start with the servo in its initial state.
Servo myServo;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output for the LED
  pinMode(motionPin, INPUT); // Initialize the pin for the motion sensor
  myServo.attach(servoPin); // Initialize the pin for the servo
  myServo.write(0); //Move the servo to a starting position
  
  //flash the LED twice to tell us that it is starting
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level but actually the LED is on;
  delay(500);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(500);                      // Wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on
  delay(500);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH

  Serial.println("Ready.");
}

// the loop function runs over and over again forever
void loop() {
  motionValue = digitalRead(motionPin); //PIR sensor pin
  if(motionValue == LOW){
    digitalWrite(LED_BUILTIN, HIGH); // Turn the  LED off
    // Change the motion state to false (no motion):
    if (motionState == true) {
      Serial.println("Motion ended!");
      motionState = false;
    }
  }
  else 
  {
    digitalWrite(LED_BUILTIN, LOW); // Turn the LED on
    // Change the motion state to true (motion detected):
    if (motionState == false) {
      Serial.println("Motion detected!");
      motionState = true;
      if (servoMoved == false){
        myServo.write(180); //Move the servo to the closed position
        servoMoved = true;
      }
    }
  }
}
