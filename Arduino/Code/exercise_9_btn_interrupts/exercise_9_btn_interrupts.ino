/*
  HES Workshop Series by HackerSchool - Arduino 
  Exercise 9 - Button with Timer2 Interupt
  When the button is pressed, the LED will be turned ON
  Same behaviour as exercise 8, only implemented with Timer2 Overflow Interrupt
*/

#define BTN 4
#define LED 11

// Volatile is a direct instruction for the compiler
// The variable will be stored in RAM, to eliminate conflicts
volatile byte pressed = LOW;

void setup() {
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  // Interrupt setup
  // Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2A = 0;
  
  // Timer2 Control Reg B: Timer Prescaler set to 1024
  TCCR2B = 1 << CS22 | 1 << CS21 | 1 << CS20;
  
  /* 
     Timer2 is 8-bits wide, so it can count up to 255.
     (255 cycles) * (1024 prescaler) / (16MHz clock speed) = 16.32 ms
     The Timer2 Overflow Interrupt will be called roughly every 16ms 
     See datasheet for more information
  */

  //Timer2 Overflow Interrupt Enable
  TIMSK2 |= 1 << TOIE2;

}

// Function to check the button
void check_button(){
  pressed = digitalRead(BTN);
}

// Code that is run when the Timer2 Overflow Interrupt is generated
SIGNAL(TIMER2_OVF_vect) {
  check_button();
}

void loop() {
  
  // Notice that the function that actually checks the button is not being explicitely called by loop()
  // But rather because of the Timer2 Overflow Interrupt
  if (pressed == LOW){
    digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);  
  }
}
