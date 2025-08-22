#include "gpio.h"

void gpio_init(GPIO_Struct *GPIO, GPIO_Init_Struct *init) {
    // The bit value for the pin when 2 bits are used per pin
    uint8_t double_pin = init->pin * 2;
    uint32_t double_mask = (0x3U << double_pin);
    uint32_t mask = (0x1U << init->pin);

    GPIO->MODER &= ~double_mask;
    GPIO->MODER |= (init->mode << double_pin);

    if (init->mode == GPIO_Mode_Output) {
        GPIO->OTYPER &= ~mask;
        GPIO->OTYPER |= (init->output_type << init->pin);
        GPIO->OSPEEDR &= ~double_mask;
        GPIO->OSPEEDR |= (init->output_speed << double_pin);
    }

    GPIO->PUPDR &= ~double_mask;
    GPIO->PUPDR |= (init->pull_up_down << double_pin);
}

void gpio_toggle(GPIO_Struct *GPIO, uint8_t pin) { GPIO->ODR ^= (0x01U << pin); }
