/*
  HES Workshop Series by HackerSchool - Arduino
  Final Sketch for the HES
  Version 1.0

  It is possible that some code will eventually be changed,
  since the Python driver that actually converts the Arduino serial ouput into actual keystrokes
  is still being worked on.
*/

#define PRESSEDLOGICLEVEL LOW // The button uses a pull-up resistor
#define DEBOUNCE 8 // (ms) half a frame at 60Hz

// Pin configuration
#define SELECT 7
#define START 12
#define UP 18
#define DOWN 2
#define LEFT 17
#define RIGHT 19
#define A 11
#define B 6

#define LED 13

// Byte array with the pin configuration
byte buttons[] = {SELECT, START, UP, DOWN, LEFT, RIGHT, A, B};
#define NUMBUTTONS sizeof(buttons)

volatile byte pressed[NUMBUTTONS], just_pressed[NUMBUTTONS], just_released[NUMBUTTONS];

void setup() {
  // Initialize serial communication at 9600 bps
  Serial.begin(9600);

  for (byte i = 0; i < NUMBUTTONS; i++)
    pinMode(buttons[i], INPUT_PULLUP);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  // Configure interrupts
  TCCR2A = 0;
  TCCR2B = 1<<CS22 | 1<<CS21 | 1<<CS20; // 1024 prescaler

  // Timer2 Overflow Interrupt Enable
  TIMSK2 |= 1<<TOIE2;

  Serial.write("Ready to Play? Type 'start' to begin.\n");

  // This will be important later for the Python driver
  while(!Serial.available())
  {
      String challenge = Serial.readString();
      if (challenge == "Hi. Who are you?" || challenge == "start" || challenge == "Start")
      {
          Serial.write("Hi. I'm HES.\n");
          break;
      }
      delay(100);
  }

  // Setup is sucessfuly over - LED on
  digitalWrite(LED, HIGH);
}

void check_buttons(){

  static byte previous_state[NUMBUTTONS];
  static byte current_state[NUMBUTTONS];
  static long last_time;
  byte index;

  // millis() returns the number of milliseconds since the program started (unsigned long)
  // This is just in case it overflows, altought that is very unlikely to happen
  if (millis() < last_time){
    last_time = millis();
  }
  if (millis() < (last_time + DEBOUNCE)) {
        return; // It hasn't been enough time since the last call to this function; must wait DEBOUNCE ms
  }
  last_time = millis(); // We have waited DEBOUNCE ms. The timer should be reset

  // Check every single button, one at a time
  for (index = 0; index < NUMBUTTONS; index++){

    current_state[index] = digitalRead(buttons[index]);   // Read the button

    if (current_state[index] != previous_state[index]) // State changed after the debounce delay
    {
      if (!pressed[index] && (current_state[index] == PRESSEDLOGICLEVEL)) {
          just_pressed[index] = true; // Just pressed
      }
      else if (pressed[index] && (current_state[index] == !PRESSEDLOGICLEVEL)) {
          just_released[index] = true; // Just released
      }

      if (PRESSEDLOGICLEVEL == HIGH){
        pressed[index] = current_state[index];
      }
      else{
        pressed[index] = !current_state[index]; // The 'pressed' byte array uses true to mean pressed
      }
    }
    previous_state[index] = current_state[index];   // Keep a running tally of the buttons
  }
}

// Code that is run when the timer2 interrupt is generated
SIGNAL(TIMER2_OVF_vect) {
  check_buttons();
}

void loop() {

  for (byte index = 0; index < NUMBUTTONS; index++){
    // If a button has just been pressed
    if (just_pressed[index]) {
        just_pressed[index] = false;
         Serial.print("P");
         Serial.println(index);
    }
    // If a button has just been released
    if (just_released[index]) {
        just_released[index] = false;
        Serial.print("R");
        Serial.println(index);
    }
  }
}
