#include <stdint.h>

#define RCC_BASE (0x40021000UL)

#define GPIOB_BASE (0x48000400UL)

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t ICSCR;
    volatile uint32_t CFGR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t PLLSAI1CFGR;
    volatile uint32_t RESERVED1;
    volatile uint32_t CIER;
    volatile uint32_t CIFR;
    volatile uint32_t CICR;
    volatile uint32_t RESERVED2;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t RESERVED3;
    volatile uint32_t APB1RSTR1;
    volatile uint32_t APB1RSTR2;
    volatile uint32_t APB2RSTR;
    volatile uint32_t RESERVED4;
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t RESERVED5;
    volatile uint32_t APB1ENR1;
    volatile uint32_t APB1ENR2;
    volatile uint32_t APB2ENR;
    volatile uint32_t RESERVED6;
    volatile uint32_t AHB1SMENR;
    volatile uint32_t AHB2SMENR;
    volatile uint32_t AHB3SMENR;
    volatile uint32_t RESERVED7;
    volatile uint32_t APB1SMENR1;
    volatile uint32_t APB1SMENR2;
    volatile uint32_t APB2SMENR;
    volatile uint32_t RESERVED8;
    volatile uint32_t CCIPR;
    volatile uint32_t RESERVED9;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t CRRCR;
    volatile uint32_t CCIPR2;
} RCC_Struct;

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
    volatile uint32_t BRR;
} GPIO_Struct;

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

static RCC_Struct *RCC = (RCC_Struct *)RCC_BASE;
static GPIO_Struct *GPIOB = (GPIO_Struct *)GPIOB_BASE;

void GPIO_init(GPIO_Struct *GPIO, GPIO_Init_Struct *init) {
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

void GPIO_toggle(GPIO_Struct *GPIO, uint8_t pin) { GPIO->ODR ^= (0x01U << pin); }

int main() {
    RCC->AHB2ENR |= (1U << 1U);

    GPIO_Init_Struct gpio_init = {.pin = 13,
                                  .mode = GPIO_Mode_Output,
                                  .output_type = GPIO_Output_Type_PushPull,
                                  .output_speed = GPIO_Output_Speed_Low,
                                  .pull_up_down = GPIO_PullUpDown_None};
    GPIO_init(GPIOB, &gpio_init);

    while (1) {
        GPIO_toggle(GPIOB, 13);
        for (int i = 0; i < 100000; i++) {
        }
    }

    return 0;
}
