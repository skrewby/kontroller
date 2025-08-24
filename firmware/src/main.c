#include "hal.h"
#include <stdint.h>

int main() {
    hal_init();

    while (1) {
        uint16_t value = (uint16_t)hal_joystick_position();
        if (value > 1400) {
            hal_led_toggle();
        }
        hal_delay(500);
    }

    return 0;
}
