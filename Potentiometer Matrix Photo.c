
#include "LedControl.h"
#include "binary.h"

// Define pins

int potPin = 14;
int photopin = 15;
int LEDPin = 3;

// LED Matrix with Max7219 controller
int DIN = 8;
int CS = 9;
int CLK = 10; 


void setup() {

   // Set pin modes for parts other than the LED Matrix
  // Inputs
  // Potentiometer
  pinMode(potPin, INPUT);
  // Photoresistor
  pinMode(photoPin, INPUT);

  // Outputs
  // LED
  pinMode(LEDPin, OUTPUT);


}

void loop() {
  
  digitalWrite(LEDPin, HIGH);

}