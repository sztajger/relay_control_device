#include <Arduino.h>
#include "led_control.h"
#include <driver/rtc_io.h>

volatile int mode = 0;
volatile unsigned long button_press_time = 0;
volatile bool active_mode = false;
volatile bool button_pressed = false;
volatile bool mode_changed = false;
volatile bool state_changed = false;

void IRAM_ATTR buttonISR() 
{
    unsigned long current_time = millis();
    int button_state = digitalRead(BUTTON_PIN);

    if (button_state == LOW && !button_pressed) // Press
    { 
        button_press_time = current_time;
        button_pressed = true;
    } 
    else if (button_state == HIGH && button_pressed) // Release
    { 
        unsigned long press_duration = current_time - button_press_time;
        button_pressed = false;

        if (press_duration < 1000) // short < 1s
        { 
            active_mode = !active_mode;
            state_changed = true;
            if (!active_mode) {
                digitalWrite(RELAY_PIN, HIGH);
                digitalWrite(LED_PIN, HIGH);
            }
        } 
        else if (press_duration >= 1000 && press_duration < 10000) // long 1s-10s
        { 
            if (active_mode) 
            {
                mode = (mode + 1) % 2;
                mode_changed = true;
            }
        }
    }
}

void setup() 
{
  Serial.begin(115200, SERIAL_8N1);
  
  setup_pins();
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, CHANGE);

  //GPIO CONFIG FOR REAL TIME CLOCK
  rtc_gpio_pulldown_dis((gpio_num_t)BUTTON_PIN);
  rtc_gpio_pullup_en((gpio_num_t)BUTTON_PIN);

  //sleep mode after start
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, 0); // 
  esp_light_sleep_start();
}

void loop() 
{
  if (active_mode) 
  {
        check_battery_and_blink(true); // BLInk in active state
        if (mode == 0) 
        {
            relay_control(1000); // 1s
            led_blink();
        } 
        else
         {
            relay_control(10000); // 10s
            led_blink();
        }
    } 
    else 
    {
        check_battery_and_blink(false); // FIX LED IS ON WHEN ESP IS OFFF
        digitalWrite(LED_PIN, LOW);    // MAKE SURE IS OFF
    }

}

