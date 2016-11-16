/*
  HES Workshop Series by HackerSchool - Arduino 
  Exercise 5 - LDR - Light Dependant Resistor
  Reads the value of an LDR sensor and prints it to the Serial Monitor
*/

#define LDR 0 // Analog 1

int sensor_value;        // Value read from the LDR

void setup() {
  Serial.begin(9600);
  pinMode(LDR, INPUT);
}

void loop() {
  
  // Read the analog in value
  // analogRead has 10 bit resolution: value from 0 to 1023
  sensor_value = analogRead(LDR);
  
  // Debug print
  Serial.print("LDR value = " );
  Serial.println(sensor_value);
  
  delay(100);
}
