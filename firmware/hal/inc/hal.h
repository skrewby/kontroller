#pragma once

#include <stdint.h>

void hal_init();
void hal_led_toggle();
void hal_delay(uint32_t ms);
void hal_serial_write(char *msg);
uint32_t hal_joystick_position();
