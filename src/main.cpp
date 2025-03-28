#include <Arduino.h>
#include "led_control.h"

// put function declarations here:
volatile int mode = 0;

void IRAM_ATTR buttonISR()
{
  unsigned long current_time = millis(); //fix debouncing problem
    if (current_time - last_debounce_time > DEBOUNCE_DELAY) 
    {
        mode = (mode + 1) % 2; //check if its long or short toggle
        last_debounce_time = current_time;
    }
}


void setup() 
{
  Serial.begin(115200);
  setup_pins();
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  Serial.println("Setup complete");
}

void loop() 
{
  int adcValue = analogRead(BATTERY_PIN); // 0-4095 (12-bit)
  float voltage = adcValue * (3.3 / 4095.0) * 3; // Przelicz na napięcie baterii
  if (voltage < BATTERY_THRESHOLD) 
  {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
  
  if (mode == 0)
  {
    relay_control(500);
    led_blink();
  }
  else
  {
    relay_control(5000);
    led_blink();
  }

  
}