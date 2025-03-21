#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "ssd1306/ssd1306.h"

#define LED_DELAY_MS 250

int main() {
    stdio_init_all();
    int rc = cyw43_arch_init();
    hard_assert(rc == PICO_OK);

    ssd1306_init(nullptr, 0, 0, 0, nullptr);

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
        sleep_ms(LED_DELAY_MS);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
        sleep_ms(LED_DELAY_MS);
    }
}
