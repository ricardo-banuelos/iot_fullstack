#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <hardware/i2c.h>

#include "ssd1306/ssd1306.h"

#define I2C_PORT i2c0
#define I2C_SDA 4  // GPIO pin for SDA
#define I2C_SCL 5  // GPIO pin for SCL
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_ADDRESS 0x3C  // Typical address for SSD1306, might be 0x3D

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
