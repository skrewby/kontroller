#pragma once

static inline void interrupts_enable(void) { __asm volatile("cpsie i" : : : "memory"); }

static inline void interrupts_disable(void) { __asm volatile("cpsid i" : : : "memory"); }
