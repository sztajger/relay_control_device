#include <Arduino.h>
#include "led_control.h"
#include <driver/rtc_io.h>



void setup_pins()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(RELAY_PIN, HIGH); // THIS WILL MAKE DIVICE OFF WHEN ESP IS IN SLEEP MODE
    //configuration gpio pins for rtc sleep mode
    rtc_gpio_init((gpio_num_t)RELAY_PIN);
    rtc_gpio_set_direction((gpio_num_t)RELAY_PIN, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level((gpio_num_t)RELAY_PIN, 1);
}

void relay_control(int delay_time) {
    unsigned long current_time = millis();
    if (current_time - last_relay_time >= delay_time) 
    {
        relay_state = !relay_state;
        digitalWrite(RELAY_PIN, relay_state);
        last_relay_time = current_time;
    }
}

void led_blink() 
{
    // LED works with relay only when batter is higher than 6V
    if (!low_battery) 
    {
        digitalWrite(LED_PIN, !digitalRead(RELAY_PIN));
    }
}

void led_on() 
{
    digitalWrite(LED_PIN, HIGH);
}

void check_battery_and_blink(bool is_avtive) {
    static unsigned long last_check_time = 0;
    static unsigned long last_battery_blink = 0;
    static bool battery_blink_state = false;
    unsigned long current_time = millis();

    // check battery voltage every 5 sec
    if (current_time - last_check_time >= 5000) 
    {
        if (battery_voltage < BATTERY_THRESHOLD) 
        {
            low_battery = true; // set flag
        } 
        else 
        {
            low_battery = false; // off flag
        }
        last_check_time = current_time;
    }

    // blink led 100ms, if battery <6V
    if (is_avtive && low_battery && current_time - last_battery_blink >= 100) 
    {
        battery_blink_state = !battery_blink_state;
        digitalWrite(LED_PIN, battery_blink_state);
        last_battery_blink = current_time;
    }
}

