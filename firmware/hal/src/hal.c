#include "hal.h"
#include "clock.h"
#include "gpio.h"
#include "interrupts.h"
#include "registers.h"
#include "systick.h"
#include <stdint.h>

static void led_init() {
    GPIO_Init_Struct led_init = {.pin = 13,
                                 .mode = GPIO_Mode_Output,
                                 .output_type = GPIO_Output_Type_PushPull,
                                 .output_speed = GPIO_Output_Speed_Low,
                                 .pull_up_down = GPIO_PullUpDown_None};
    gpio_init(GPIOB, &led_init);
}

static void setup_clock() {
    RCC_Init_Struct rcc_init = {
        .clock = RCC_CLOCK_HSI,
    };
    clock_init(&rcc_init);
}

void hal_init() {
    interrupts_disable();
    setup_clock();
    led_init();
    systick_init();
    interrupts_enable();
}

void hal_led_toggle() { gpio_toggle(GPIOB, 13); }

void hal_delay(uint32_t ms) {
    uint32_t start = systick_value();
    while ((systick_value() - start) < ms) {
    }
}
