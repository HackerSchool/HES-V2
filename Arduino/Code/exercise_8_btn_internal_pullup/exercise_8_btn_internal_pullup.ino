/*
  HES Workshop Series by HackerSchool - Arduino 
  Exercise 8 - Button with internal pull-up resistor
  When the button is pressed, the LED will be turned ON
*/

#define BTN 4
#define LED 11

int button_state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  button_state = digitalRead(BTN);
  if (button_state == HIGH){
    digitalWrite(LED, HIGH);  
  }else{
    digitalWrite(LED, LOW);  
  }
  delay(50); // Debounce
}
