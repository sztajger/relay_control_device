#include <Arduino.h>
#include "led_control.h"

// put function declarations here:
volatile int mode = 0;

void IRAM_ATTR buttonISR()
{
  mode = (mode + 1) % 2;
}
void setup() {
  
  // put your setup code here, to run once:
  setup_pins();
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop() {
  
  if (mode == 0)
  {
    led_on();
  }else
  {
    led_blink(500);
  }


  // put your main code here, to run repeatedly:
}

