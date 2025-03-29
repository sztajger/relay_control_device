#include <Arduino.h>
#include "led_control.h"

static unsigned long last_relay_time = 0;
const float battery_voltage = 5.5; //hardcode battery voltage, esp32 its bad at reading real battery 
static bool relay_state = false;
static bool low_battery = false; // state flag

void setup_pins()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
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

void check_battery_and_blink() {
    static unsigned long last_check_time = 0;
    static unsigned long last_battery_blink = 0;
    static bool battery_blink_state = false;
    unsigned long current_time = millis();

    // check battery voltage every 5 sec
    if (current_time - last_check_time >= 5000) 
    {
        if (battery_voltage < BATTERY_THRESHOLD) 
        {
            Serial.print("Low Battery: ");
            Serial.print(battery_voltage);
            Serial.println("V");
            low_battery = true; // set flag
        } 
        else 
        {
            low_battery = false; // off flag
        }
        last_check_time = current_time;
    }

    // blink led 100ms, if battery <6V
    if (low_battery && current_time - last_battery_blink >= 100) 
    {
        battery_blink_state = !battery_blink_state;
        digitalWrite(LED_PIN, battery_blink_state);
        last_battery_blink = current_time;
    }
}

void show_battery_status() // 
{
    static unsigned long last_status_time = 0;
    unsigned long current_time = millis();

    if (current_time - last_status_time >= 5000) 
    {
        Serial.print("Battery: ");
        Serial.print(battery_voltage);
        Serial.println("V");
        last_status_time = current_time;
    }
}