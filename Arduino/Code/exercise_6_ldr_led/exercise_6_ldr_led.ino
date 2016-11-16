/*
  HES Workshop Series by HackerSchool - Arduino 
  Exercise 6 - LDR Input and PWM LED output
  Uses the value read from an analog sensor to control the brightness of and LED light
*/

#define LED 9 // Digital 11 ~
#define LDR A1 // Analog 1

#define INPUT_m 0         // These values should be fined tuned for higher precision
#define INPUT_M 1023

int sensor_value = 0;        // Value read from the LDR
int output_value = 0;        // Value output to the PWM ("analog" out)

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  // Read the analog input value
  sensor_value = analogRead(LDR);
  
  // Map it to the range of the analog out
  // map(input_var, input_min, input_max, output_min, output_max) 
  output_value = map(sensor_value, INPUT_m, INPUT_M, 0, 255);
  
  // Change the analog out value:
  analogWrite(LED, output_value);
  
  // Debug print
  Serial.print("LDR value = " );
  Serial.print(sensor_value);
  Serial.print("\t LED value = ");
  Serial.println(output_value); 
  
  delay(100);
}
