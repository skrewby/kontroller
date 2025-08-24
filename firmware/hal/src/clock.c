#include "clock.h"
#include <stdbool.h>
#include <stdint.h>

static uint32_t system_clock = 0;

#define RCC_AHB2ENR_GPIOAEN (1U << 0)
#define RCC_AHB2ENR_GPIOBEN (1U << 1)
#define RCC_AHB2ENR_GPIOCEN (1U << 2)
#define RCC_AHB2ENR_ADCEN   (1U << 13)

#define RCC_APB1ENR1_USART2EN (1U << 17)

#define RCC_CR_HSION  (1U << 8)
#define RCC_CR_HSIRDY (1U << 10)

#define RCC_CFGR_SW_BIT  (0)
#define RCC_CFGR_SWS_BIT (2)

typedef enum {
    RCC_SWS_CLOCK_MSI,
    RCC_SWS_CLOCK_HSI16,
    RCC_SWS_CLOCK_HSE,
    RCC_SWS_CLOCK_PLL,
} RCC_SWS_CLOCK;

static bool is_system_clock(RCC_SWS_CLOCK clock) {
    uint8_t value = (RCC->CFGR >> RCC_CFGR_SWS_BIT) & 0xFF;
    return value == clock;
}

static void hsi_setup() {
    RCC->CR |= RCC_CR_HSION;

    while (!(RCC->CR & RCC_CR_HSIRDY)) {
    }

    RCC->CFGR &= ~(0x3 << RCC_CFGR_SW_BIT);
    RCC->CFGR |= 0x1 << RCC_CFGR_SW_BIT;

    while (!is_system_clock(RCC_SWS_CLOCK_HSI16)) {
    }

    system_clock = 16000000UL;
}

void clock_init(RCC_Init_Struct *init) {
    RCC->CR = 0;
    switch (init->clock) {
    case RCC_CLOCK_HSI:
        hsi_setup();
        break;
    }

    RCC->AHB2ENR |=
        (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_ADCEN);
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
}

uint32_t clock_frequency() { return system_clock; }
