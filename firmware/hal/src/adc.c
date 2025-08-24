#include "adc.h"
#include "gpio.h"
#include "registers.h"
#include <stdint.h>

#define ADC_CR_ADEN     (1U << 0)
#define ADC_CR_ADSTART  (1U << 2)
#define ADC_CR_ADVREGEN (1U << 28)
#define ADC_CR_DEEPPWD  (1U << 29)
#define ADC_CR_ADCAL    (1U << 31)

#define ADC_CFGR_RES_BIT    (3)
#define ADC_CFGR_CONT_BIT   (13)
#define ADC_CFGR_EXTEN_BIT  (10)
#define ADC_CFGR_EXTSEL_BIT (6)
#define ADC_CFGR_ALIGN_BIT  (5)
#define ADC_SQR1_SQ1_BIT    (6)
#define ADC_SQR1_L_BIT      (0)

#define ADC_ISR_ADRDY (1U << 0)
#define ADC_ISR_EOC   (1U << 2)

#define ADC_COMMON_CCR_CKMODE_BIT (16)

static void setup_gpio() {
    GPIO_Init_Struct init = {
        .pin = 0,
        .mode = GPIO_Mode_Analog,
        .pull_up_down = GPIO_PullUpDown_None,
    };
    gpio_init(GPIOC, &init);
}

static void calibrate() {
    ADC->CR |= ADC_CR_ADCAL;

    while (ADC->CR & ADC_CR_ADCAL) {
    }
}

void adc_init() {
    ADC->CR &= ~ADC_CR_DEEPPWD;
    ADC->CR |= ADC_CR_ADVREGEN;

    // We will get the clock from AHB2 divided by 2
    ADCCOMMON->CCR &= ~(0xFU << ADC_COMMON_CCR_CKMODE_BIT);
    ADCCOMMON->CCR |= (0x2U << ADC_COMMON_CCR_CKMODE_BIT);

    ADC->CR &= ~(ADC_CR_ADEN);

    setup_gpio();

    calibrate();

    ADC->CFGR &= ~(0x3U << ADC_CFGR_RES_BIT);
    ADC->CFGR &= ~(0x3U << ADC_CFGR_EXTEN_BIT);
    ADC->CFGR &= ~(0x1U << ADC_CFGR_ALIGN_BIT);

    ADC->SQR1 &= ~(0xFU << ADC_SQR1_L_BIT);
    ADC->SQR1 &= ~(0x1FU << ADC_SQR1_SQ1_BIT);
    ADC->SQR1 |= (0x1U << ADC_SQR1_SQ1_BIT);

    ADC->CR |= ADC_CR_ADEN;
    while (!(ADC->ISR & ADC_ISR_ADRDY)) {
    }
}

uint32_t adc_read() {
    ADC->CR |= ADC_CR_ADSTART;

    while (!(ADC->ISR & ADC_ISR_EOC)) {
    }

    return ADC->DR;
}
