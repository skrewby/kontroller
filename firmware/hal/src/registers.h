#pragma once

#include <stdint.h>

#define SYSTICK_BASE    (0xE000E010UL)
#define USART2_BASE     (0x40004400UL)
#define RCC_BASE        (0x40021000UL)
#define GPIOA_BASE      (0x48000000UL)
#define GPIOB_BASE      (0x48000400UL)
#define GPIOC_BASE      (0x48000800UL)
#define ADC_BASE        (0x50040000UL)
#define ADC_COMMON_BASE (ADC_BASE + 0x300)

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

typedef struct {
    volatile uint32_t CSR;
    volatile uint32_t RVR;
    volatile uint32_t CVR;
    volatile uint32_t CALIB;
} SysTick_Struct;

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t BRR;
    volatile uint16_t GTPR;
    volatile uint16_t RESERVED1;
    volatile uint32_t RTOR;
    volatile uint16_t RQR;
    volatile uint16_t RESERVED2;
    volatile uint32_t ISR;
    volatile uint32_t ICR;
    volatile uint16_t RDR;
    volatile uint16_t RESERVED3;
    volatile uint16_t TDR;
    volatile uint16_t RESERVED4;
} USART_Struct;

typedef struct {
    volatile uint32_t ISR;
    volatile uint32_t IER;
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CFGR2;
    volatile uint32_t SMPR1;
    volatile uint32_t SMPR2;
    volatile uint32_t RESERVED1;
    volatile uint32_t TR1;
    volatile uint32_t TR2;
    volatile uint32_t TR3;
    volatile uint32_t RESERVED2;
    volatile uint32_t SQR1;
    volatile uint32_t SQR2;
    volatile uint32_t SQR3;
    volatile uint32_t SQR4;
    volatile uint32_t DR;
    volatile uint32_t RESERVED3;
    volatile uint32_t RESERVED4;
    volatile uint32_t JSQR;
    volatile uint32_t RESERVED5[4];
    volatile uint32_t OFR1;
    volatile uint32_t OFR2;
    volatile uint32_t OFR3;
    volatile uint32_t OFR4;
    volatile uint32_t RESERVED6[4];
    volatile uint32_t JDR1;
    volatile uint32_t JDR2;
    volatile uint32_t JDR3;
    volatile uint32_t JDR4;
    volatile uint32_t RESERVED7[4];
    volatile uint32_t AWD2CR;
    volatile uint32_t AWD3CR;
    volatile uint32_t RESERVED8;
    volatile uint32_t RESERVED9;
    volatile uint32_t DIFSEL;
    volatile uint32_t CALFACT;

} ADC_Struct;

typedef struct {
    volatile uint32_t RESERVED1;
    volatile uint32_t RESERVED2;
    volatile uint32_t CCR;
    volatile uint32_t RESERVED3;
} ADC_Common_Struct;

static RCC_Struct *RCC = (RCC_Struct *)RCC_BASE;
static GPIO_Struct *GPIOA = (GPIO_Struct *)GPIOA_BASE;
static GPIO_Struct *GPIOB = (GPIO_Struct *)GPIOB_BASE;
static GPIO_Struct *GPIOC = (GPIO_Struct *)GPIOC_BASE;
static SysTick_Struct *SYSTICK = (SysTick_Struct *)SYSTICK_BASE;
static USART_Struct *USART2 = (USART_Struct *)USART2_BASE;
static ADC_Struct *ADC = (ADC_Struct *)ADC_BASE;
static ADC_Common_Struct *ADCCOMMON = (ADC_Common_Struct *)ADC_COMMON_BASE;
