#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#define LED_PIN 2
#define RELAY_PIN 18

#define BATTERY_PIN 34
#define BATTERY_THRESHOLD 6.0 // battery 6v barrier

#define BUTTON_PIN 15
#define DEBOUNCE_DELAY 300;
#define SHORT_PRESS_TIME 1000;

void setup_pins();
void relay_control(int delay_time);
void led_blink();
void check_battery_and_blink(bool is_avtive);
void led_on();

#endif