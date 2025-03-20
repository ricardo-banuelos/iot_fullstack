#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <hardware/i2c.h>

int main() {
    stdio_init_all();

    // Initialize the Pico W's onboard wireless chip (which also controls the LED)
    if (cyw43_arch_init()) {
        return -1; // Failed to initialize
    }

    // Main loop
    while (true) {
        // Turn on the LED (connected to the wireless chip on the Pico W)
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);  // Sleep for 500ms
        
        // Turn off the LED
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);  // Sleep for 500ms
    }

    // We'll never reach here due to the infinite loop
    cyw43_arch_deinit();
    return 0;
}
