#pragma once

#include "registers.h"
#include <stdint.h>

typedef enum {
    RCC_CLOCK_HSI,
} RCC_CLOCK;

typedef struct {
    RCC_CLOCK clock;
} RCC_Init_Struct;

void clock_init(RCC_Init_Struct *init);
uint32_t clock_frequency();
