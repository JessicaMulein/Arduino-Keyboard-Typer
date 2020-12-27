#include <Keyboard.h>

const int SWITCH_PIN = 7; // Pin with interrupts available
const int LED_PIN = 17;   // Sparkfun Pro Micro 5V RX/TX LED
const char passwd[] = ""; // add your password

bool ledState = false;
volatile bool isrTriggered = false; // changed in ISR

// don't do anything long/stacky
void isr() {
  isrTriggered = true;
}

void setup() {
  isrTriggered = false;
  ledState = false;
  pinMode(SWITCH_PIN, INPUT_PULLUP); // switch
  pinMode(LED_PIN, OUTPUT); // LED
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), isr, FALLING);
  Keyboard.begin();
}

void setLed(bool val) {
  ledState = val;
  digitalWrite(LED_PIN, ledState);
}

void toggleLed() {
  setLed(!ledState);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (1) {
    if (isrTriggered) {
      setLed(true);
      Keyboard.print(passwd);
      delay(500);
      isrTriggered=false;
    }
    delay(500);
    toggleLed();
  }
}
