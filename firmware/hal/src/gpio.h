#pragma once

#include "registers.h"
#include <stdint.h>

typedef enum {
    GPIO_Mode_Input,
    GPIO_Mode_Output,
    GPIO_Mode_Alternate,
    GPIO_Mode_Analog,
} GPIO_MODE;

typedef enum {
    GPIO_Output_Type_PushPull,
    GPIO_Output_Type_OpenDrain,
} GPIO_OUTPUT_TYPE;

typedef enum {
    GPIO_Output_Speed_Low,
    GPIO_Output_Speed_Medium,
    GPIO_Output_Speed_High,
    GPIO_Output_Speed_VeryHigh,
} GPIO_OUTPUT_SPEED;

typedef enum {
    GPIO_PullUpDown_None,
    GPIO_PullUpDown_PullUp,
    GPIO_PullUpDown_PullDown,
} GPIO_PULLUP_DOWN;

typedef struct {
    uint8_t pin;
    GPIO_MODE mode;
    GPIO_OUTPUT_TYPE output_type;
    GPIO_OUTPUT_SPEED output_speed;
    GPIO_PULLUP_DOWN pull_up_down;
} GPIO_Init_Struct;

void gpio_toggle(GPIO_Struct *GPIO, uint8_t pin);
void gpio_init(GPIO_Struct *GPIO, GPIO_Init_Struct *init);
