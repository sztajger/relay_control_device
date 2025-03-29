#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#define LED_PIN 2
#define RELAY_PIN 18
#define BUTTON_PIN 15
#define BATTERY_PIN 34
#define BATTERY_THRESHOLD 6.0 // battery 6v

void setup_pins();
void relay_control(int delay_time);
void led_blink();
void check_battery_and_blink();
void show_battery_status();
void led_on();

#endif