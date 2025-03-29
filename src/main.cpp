#include <Arduino.h>
#include "led_control.h"

volatile int mode = 0;
const int DEBOUNCE_DELAY = 300; 
unsigned long last_debounce_time = 0;

void IRAM_ATTR buttonISR() {
    unsigned long current_time = millis();
    if (current_time - last_debounce_time > DEBOUNCE_DELAY) {
        mode = (mode + 1) % 2;
        last_debounce_time = current_time;
    }
}

void setup() 
{
  Serial.begin(115200);
  setup_pins();
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, CHANGE);
  Serial.println("Setup complete");
}

void loop() 
{
  check_battery_and_blink();
  show_battery_status();

  if (mode == 0)
  {
    relay_control(500);
  }
  else if (mode ==1)
  {
    relay_control(5000);
  }

}

