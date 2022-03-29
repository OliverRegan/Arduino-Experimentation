#include <LCD_I2C.h>

// Define hardware pins

// Define LCD
LCD_I2C lcd(0x27);

// Define button for LCD change
const int buttonPin = 2;




// Define global Variables

// Define variables for button changes
int buttonState = 0;
int lastButtonState = 0; 

// Define variables for the ultrasonic sensor
int trigPin = 7;
int echoPin = 6;
long duration, cm, inches;


// Define stuff for motor driver
// Motor A connections
int enA = 13;
int in1 = 8;
int in2 = 9;
// Motor B connections
int enB = 12;
int in3 = 10;
int in4 = 11;


// ======================== Main setup ========================

void setup() {

  // Start LCD  
  lcd.begin();
  lcd.backlight();
  lcd.print("Hello");

  // Setup inputs and outputs

  // Setup button
  pinMode(buttonPin, INPUT);

  // Setup Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);



  // Setup motors
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


// ======================== Main Loop ========================

void loop() {

  process();
  
}


// ======================== Main function ========================
void process(){

  if(btnEdgeDetection() == 1){
    writeScrollText("Paige is the love of my life <3");

    lcd.clear();
  } 
    

  // Ultrasonic - send out 10 microsecond burst to measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Receive sound back in echo pin  
  duration = pulseIn(echoPin, HIGH);

  // Convert time between burst and receiving to distance by 2 to account for the sound travelling both ways then by the speed of sound into cm
  cm = (duration/2) / 29.1;

  lcd.print("Distance:");
  lcd.print(cm); 

  delay(500);

  



  directionControl();
  delay(1000);
  speedControl();
  delay(1000);

  lcd.clear();
}


// ======================== Other functions ========================

// Write scrolling text
void writeScrollText(String text){

  lcd.clear();

  //  Print input text
  lcd.print(text);

  delay(2000);

  int txtLength = text.length();

  
  
  
  for(int i = 0; i < (txtLength - 16); i++){
    
    lcd.scrollDisplayLeft();
    delay(500);
    
  }

  delay(2000);
  
  lcd.clear();
    
}

// Check button press for rising or falling edge - returns true on button press or false on button off
int btnEdgeDetection(){
  
  // Read button state
  buttonState = digitalRead(buttonPin);


  // Compare to prev state
  if(buttonState != lastButtonState){

    // Check to see if it went from LOW to HIGH - meaning the button has been pressed
    if(buttonState == HIGH){

      // Button is pressed, return true
      return 1;

    } else {

      // Button is off - return false
      return 0;

    }

    // Include small delay for debouncing
    delay(15);

  }

  // Change last button state to current button state
  lastButtonState = buttonState;

  //  if nothing found, return 3

  return 3;

}


// This function lets you control spinning direction of motors
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);
  
  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);
  
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}