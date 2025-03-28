#include <Arduino.h>
#include "led_control.h"

static int mode = 0;
static int last_button_state = HIGH;
static const int DEBOUNCE_DELAY = 50;
static long last_debounce_time = 0;

void setup_pins()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    digitalWrite(LED_PIN, HIGH);
}

void led_on ()
{
    digitalWrite(LED_PIN, HIGH);
}

void led_blink (int delay_time)
{
    digitalWrite(LED_PIN, HIGH);
    delay(delay_time);
    digitalWrite(LED_PIN, LOW);
    delay(delay_time);
}
