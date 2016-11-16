/*
  HES Workshop Series by HackerSchool - Arduino 
  Exercise 4 - LED PWM
  Shows the PWM capabilities of certain pins, by making an LED light fade in and out repeatedly.   
  Based on the Fade.ino example. 
*/

#define LED 9
#define MIN 0
#define MAX 255

int brightness = 0; // Duty Cicle variable
int fade_step = 5;

void setup() {
  pinMode(LED, OUTPUT);
}


void loop() {
  
  analogWrite(LED, brightness); // 8 bit value - 0 to 255 
  
  brightness = brightness + fade_step;
  
  // If the brightness has reached one of the limit values
  if (brightness == MIN || brightness == MAX) {
    // The step will now be done in the opposite direction
    fade_step = -fade_step ;
  }
  
  delay(50);
}
