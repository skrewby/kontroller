#include "interrupts.h"
#include "systick.h"

void SysTick_Handler() { systick_increment(); }
