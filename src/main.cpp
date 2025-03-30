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


void loop() 
{
