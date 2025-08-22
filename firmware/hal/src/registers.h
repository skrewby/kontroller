#pragma once

#include <stdint.h>

#define RCC_BASE   (0x40021000UL)
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

static RCC_Struct *RCC = (RCC_Struct *)RCC_BASE;
static GPIO_Struct *GPIOB = (GPIO_Struct *)GPIOB_BASE;
