#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#define LED_PIN 2
#define BUTTON_PIN 5

void setup_pins();
void led_on();
void led_blink(int delay_time);
void button_change_toggle();

#endif
