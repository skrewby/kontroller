#pragma once

#include <stdint.h>

void systick_init();
void systick_increment();
uint32_t systick_value();
