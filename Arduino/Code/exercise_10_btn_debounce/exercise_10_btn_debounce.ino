/*
  HES Workshop Series by HackerSchool - Arduino 
  Exercise 10 - Button with Timer2 Interupt and propper debounce logic
  The Arduino is now be able to tell whether a button has just been pressed or just been released
*/

#define PRESSEDLOGICLEVEL LOW
#define DEBOUNCE 8 // (ms) half a frame at 60Hz

#define BTN 4
#define LED 11

volatile byte pressed, just_pressed, just_released;

void setup() {
  Serial.begin(9600);
  
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  digitalWrite(LED, LOW);
  
  // Timer2 Overflow Interrupt setup
  TCCR2A = 0;
  TCCR2B = 1<<CS22 | 1<<CS21 | 1<<CS20;
  //Timer2 Overflow Interrupt Enable
  TIMSK2 |= 1<<TOIE2;
  
  // Setup is sucessfuly over - LED is turned ON
  digitalWrite(LED, HIGH);
}

// Function to check the button
void check_button(){
  
  static byte previous_state;
  static byte current_state;
  static long last_time;
  
  // millis() returns the number of milliseconds since the program started (unsigned long)
  // This is just in case it overflows, altought that is very unlikely to happen
  if (millis() < last_time){
    last_time = millis();  
  }
  if (millis() < (last_time + DEBOUNCE)) {
        return; // It hasn't been enough time since the last call to this function; must wait DEBOUNCE ms
  }
  last_time = millis(); // We have waited DEBOUNCE ms. The timer should be reset
  
  current_state = digitalRead(BTN);   // Read the state of button
     
  if (current_state != previous_state) // State changed after the debounce delay
  {
    if (!pressed && (current_state == PRESSEDLOGICLEVEL)) {              
        just_pressed = true; // Just pressed
    }
    else if (pressed && (current_state == !PRESSEDLOGICLEVEL)) {              
        just_released = true; // Just released
    }
    
    if (PRESSEDLOGICLEVEL == HIGH) 
      pressed = current_state;   
    else 
      pressed = !current_state; // The 'pressed' byte uses true to mean pressed 
  }
  previous_state = current_state;   // Keep a running tally of the buttons
}

// Code that is run when the timer2 interrupt is generated
SIGNAL(TIMER2_OVF_vect) {
  check_button();
}

void loop() {
  
    if (just_pressed) {
        just_pressed = false;
        Serial.println("Just pressed the button!");            
    }
    if (just_released) {
        just_released = false;
        Serial.println("Just released the button!");
    }    
}
