/*
  HES Workshop Series by HackerSchool - Arduino 
  Exercise 2 - Blink LED
  Blinks an LED on pin 13 
  (Arduino boards usually have an LED built-in associated with pin 13)
  Based on the Blink.ino example
*/

#define LED 13

void setup() {
  // Configure the LED pin for output
  pinMode(LED, OUTPUT);  
}

void loop() {
  // Turns the LED light on
  digitalWrite(LED, HIGH);
  delay(1000);
  // Turns the LED light off
  digitalWrite(LED, LOW);
  delay(1000);
}
