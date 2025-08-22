#include "hal.h"

int main() {
    hal_init();

    while (1) {
        hal_led_toggle();
        hal_serial_write("Hello\r\n");
        hal_delay(1000);
    }

    return 0;
}
