/*
  HES Workshop Series by HackerSchool - Arduino 
  Exercise 3 - LED Toggle with Serial Read
  Toggles the state of an LED when 't' is sent via Serial
*/ 

#define LED 13

// Boolean variables can only be either 0 or 1. They are natively supported
bool led_state = false;
   
void setup(){
   
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}
 
void loop(){
      
  if (Serial.read() == 't'){
     // Toggle the LED state
     led_state = ! led_state;
     digitalWrite(LED, led_state);
   }
   delay(100); // The delay is optional but useful
 }          
