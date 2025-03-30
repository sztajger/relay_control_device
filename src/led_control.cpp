#include <Arduino.h>
#include "led_control.h"
#include <driver/rtc_io.h>



void setup_pins()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
