#include "uart.h"
#include "clock.h"
#include "gpio.h"

#define USART_CR1_UE     (1U << 0)
#define USART_CR1_RE     (1U << 2)
#define USART_CR1_TE     (1U << 3)
#define USART_CR1_RXNEIE (1U << 5)

#define USART_ISR_TXE (1U << 7)

static void setup_gpio() {
    GPIO_Init_Struct pa2_init = {
        .pin = 2,
        .mode = GPIO_Mode_Alternate,
        .output_type = GPIO_Output_Type_PushPull,
        .output_speed = GPIO_Output_Speed_High,
        .alternate_function = GPIO_AlternateFunction_7,
    };
    gpio_init(GPIOA, &pa2_init);

    GPIO_Init_Struct pa3_init = {
        .pin = 3,
        .mode = GPIO_Mode_Alternate,
        .output_type = GPIO_Output_Type_PushPull,
        .output_speed = GPIO_Output_Speed_High,
        .alternate_function = GPIO_AlternateFunction_7,
    };
    gpio_init(GPIOA, &pa3_init);
}

void uart_init(UART_Init_Struct *init) {
    setup_gpio();

    uint32_t div = clock_frequency() / init->baud_rate;
    USART2->BRR = div;
    USART2->CR1 |= (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE);
}

void uart_write(uint16_t ch) {
    while (!(USART2->ISR & USART_ISR_TXE)) {
    }

    USART2->TDR = ch;
}
