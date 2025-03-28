#include <Arduino.h>
#include "led_control.h"

static int last_button_state = HIGH;
static const int DEBOUNCE_DELAY = 50;
static long last_debounce_time = 0;

void setup_pins()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    digitalWrite(LED_PIN, LOW);
}

void led_blink()
{
    if(digitalRead(RELAY_PIN) == HIGH)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }
}

void relay_control (int delay_time)
{
    digitalWrite(RELAY_PIN, HIGH);
    delay(delay_time);
    digitalWrite(RELAY_PIN, LOW);
    delay(delay_time);
}

void led_on() {
    digitalWrite(LED_PIN, HIGH);
}

void check_battery_and_blink()
{

}