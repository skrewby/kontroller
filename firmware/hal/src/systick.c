#include "systick.h"
#include "clock.h"
#include "registers.h"
#include <stdint.h>

#define SYSTICK_CSR_ENABLE  (1U << 0)
#define SYSTICK_CSR_TICKINT (1U << 1)
// Set processor clock
#define SYSTICK_CSR_CLKSOURCE (1U << 2)

static volatile uint32_t systick_counter = 0;

void systick_init() {
    SYSTICK->CSR = 0;

    // We want to tick every ms
    SYSTICK->RVR = clock_frequency() / 1000;

    SYSTICK->CVR = 0;

    SYSTICK->CSR = SYSTICK_CSR_ENABLE | SYSTICK_CSR_TICKINT | SYSTICK_CSR_CLKSOURCE;
}

void systick_increment() { systick_counter++; }

uint32_t systick_value() { systick_counter; }
