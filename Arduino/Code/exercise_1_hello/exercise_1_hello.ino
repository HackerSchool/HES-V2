/*
  HES Workshop Series by HackerSchool - Arduino 
  Exercise 1 - Hello World
  Prints Hello World! to the terminal every second
*/

// The setup routine runs once when the Arduino is turned on, or anytime the RESET button is pressed
void setup() {
  // Initiate Serial Communication with a baudrate of 9600 bps
  Serial.begin(9600);
}

// The loop routine runs over and over again
void loop() {
  // Prints "Hello World!" to the serial monitor 
  Serial.println("Hello World!");
  delay(1000);
}
