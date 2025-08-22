#pragma once

#include <stdint.h>

typedef struct {
    uint32_t baud_rate;
} UART_Init_Struct;

void uart_init(UART_Init_Struct *init);
void uart_write(uint16_t ch);
