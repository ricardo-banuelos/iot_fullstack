add_library(ssd1306 
    ssd1306.c)

target_link_libraries(ssd1306
    pico_stdlib
    pico_cyw43_arch_none
    hardware_i2c)