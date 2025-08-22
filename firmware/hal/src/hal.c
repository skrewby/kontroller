#include "hal.h"
#include "gpio.h"
#include "registers.h"

void hal_init() {
    RCC->AHB2ENR |= (1U << 1U);

    GPIO_Init_Struct led_init = {.pin = 13,
                                 .mode = GPIO_Mode_Output,
                                 .output_type = GPIO_Output_Type_PushPull,
                                 .output_speed = GPIO_Output_Speed_Low,
                                 .pull_up_down = GPIO_PullUpDown_None};
    gpio_init(GPIOB, &led_init);
}

void hal_led_toggle() { gpio_toggle(GPIOB, 13); }
