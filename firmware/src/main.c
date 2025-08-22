#include "hal.h"

int main() {
    hal_init();

    while (1) {
        hal_led_toggle();
        for (int i = 0; i < 100000; i++) {
        }
    }

    return 0;
}
